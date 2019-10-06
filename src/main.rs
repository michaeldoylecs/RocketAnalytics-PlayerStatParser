extern crate boxcars;
extern crate csv;
extern crate dirs;
extern crate serde;
#[macro_use]
extern crate serde_derive;

use boxcars::{ParseError, Replay, HeaderProp};

use std::error;
use std::fs;
use std::io::{stdin, Read, Error, ErrorKind};
use std::path::*;
use std::string::*;

#[derive(Default, Debug, Clone, Serialize)]
struct PlayerStats {
    name: String,
    platform: String,
    platform_id: u64,
    team: i32,
    games_players: i32,
    mvp: bool,
    points: i32,
    goals: i32,
    assists: i32,
    saves: i32,
    shots: i32
}

impl PlayerStats {
    fn default() -> PlayerStats {
        PlayerStats {
            name: "".to_string(),
            platform: "".to_string(),
            platform_id: 0,
            team: -1,
            games_players: 0,
            mvp: false,
            points: 0,
            goals: 0,
            assists: 0,
            saves: 0,
            shots: 0
        }
    }
}

fn prompt_for_user_input(prompt: &str) -> String {
    println!("{}", prompt);
    let mut input = String::new();
    stdin().read_line(&mut input).unwrap();
    input.trim_start().trim_end().to_string()
}

fn read_path_input(prompt: &str) -> Result<PathBuf, String> {
    let input = prompt_for_user_input(prompt);
    let raw_path = PathBuf::from(input);
    let full_path = match fs::canonicalize(raw_path) {
        Ok(path) => path,
        Err(error) => return Err(error.to_string()),
    };
    if !full_path.is_dir() {
        return Err("Given path is not a valid directory!".to_string());
    }
    Ok(full_path)
}

fn parse_replay_data(data: &[u8]) -> Result<Replay, ParseError> {
    boxcars::ParserBuilder::new(data)
        .always_check_crc()
        .never_parse_network_data()
        .parse()
}

fn parse_replay(path: &Path) -> Result<Replay, Box<dyn error::Error>> {
    let mut file = fs::File::open(path)?;
    let mut file_buffer = Vec::new();
    file.read_to_end(&mut file_buffer)?;
    match parse_replay_data(&file_buffer) {
        Ok(replay) => return Ok(replay),
        Err(e)     => return Err(Box::new(e)),
    }
}

fn set_mvp(players: Vec<PlayerStats>, winning_team: i32) -> Vec<PlayerStats> {
    let mut highest_scoring_player: PlayerStats = PlayerStats::default();
    for player in players.iter() {
        if player.team == winning_team {
            if player.points > highest_scoring_player.points {
                highest_scoring_player = player.clone();
            }
        }
    }
    let mut new_player_list = players.clone();
    for player in new_player_list.iter_mut() {
        if player.platform_id == highest_scoring_player.platform_id {
            player.mvp = true;
            break;
        }
    }
    new_player_list
}

fn make_player_stats(props: Vec<(String, HeaderProp)>) -> PlayerStats {
    let mut player = PlayerStats::default();
    for prop in props {
        let id = prop.0;
        let val = prop.1;
        match id.as_ref() {
            "Name"     => if let HeaderProp::Str(s) = val { player.name = s; },
            "Platform" => if let HeaderProp::Byte = val { player.platform = "N/A".to_string(); },
            "OnlineID" => if let HeaderProp::QWord(n) = val { player.platform_id = n; },
            "Team"     => if let HeaderProp::Int(n) = val { player.team = n; },
            "Score"    => if let HeaderProp::Int(n) = val { player.points = n; },
            "Goals"    => if let HeaderProp::Int(n) = val { player.goals = n; },
            "Assists"  => if let HeaderProp::Int(n) = val { player.assists = n; },
            "Saves"    => if let HeaderProp::Int(n) = val { player.saves = n; },
            "Shots"    => if let HeaderProp::Int(n) = val { player.shots = n; },
            _          => (),
        }
    }
    player
}

fn get_stats_from_player_stats(replay_stats: HeaderProp, winning_team: i32) -> Vec<PlayerStats> {
    let mut stats = Vec::new();
    if let HeaderProp::Array(values) = replay_stats {
        for player_info in values {
            let player_stats = make_player_stats(player_info);
            stats.push(player_stats);
        }
    }
    stats = set_mvp(stats, winning_team);
    stats
}

fn get_player_stats_property(replay: &Replay) -> Result<HeaderProp, String> {
    for property in &replay.properties {
        if property.0 == "PlayerStats" {
            return Ok(property.1.clone());
        }
    }
    Err("PlayerStats Property not found!".to_string())
}

fn get_winning_team(replay: &Replay) -> Result<i32, String> {
    let mut team_0_score: i32 = 0;
    let mut team_1_score: i32 = 0;
    for prop in &replay.properties {
        match prop.0.as_ref() {
            "Team0Score" => if let HeaderProp::Int(v) = prop.1 { team_0_score = v },
            "Team1Score" => if let HeaderProp::Int(v) = prop.1 { team_1_score = v },
            _            => (),
        }
    }
    return if team_0_score < team_1_score { Ok(1) } else { Ok(0) }
}

fn write_csv(stats: Vec<PlayerStats>, output: PathBuf) -> Result<(), Box<dyn error::Error>> {
    let mut csv_wtr = csv::WriterBuilder::new()
        .has_headers(false)
        .from_path(output)?;
    csv_wtr.write_record(&[
                         "Name",
                         "Platform",
                         "OnlineID",
                         "Games Played",
                         "MVPs",
                         "Points",
                         "Goals",
                         "Assists",
                         "Saves",
                         "Shots"])?;
    for stat in stats.iter() {
        let name = stat.name.clone();
        let platform = stat.platform.clone();
        let online_id = stat.platform_id.to_string();
        let games_played = 1.to_string();
        let mvps = if stat.mvp { "1".to_string() } else { "0".to_string() };
        let score = stat.points.to_string();
        let goals = stat.goals.to_string();
        let assists = stat.assists.to_string();
        let saves = stat.saves.to_string();
        let shots = stat.shots.to_string();
        csv_wtr.write_record(&[name,
                             platform,
                             online_id,
                             games_played,
                             mvps,
                             score,
                             goals,
                             assists,
                             saves,
                             shots])?;
    }
    csv_wtr.flush()?;
    Ok(())
}

fn run() -> Result<(), Box<dyn error::Error>> {
    let input_path: PathBuf = read_path_input("What is the path to the replay file directory")?;
    let mut output_path: PathBuf = read_path_input("What is the path to the output directory")?;
    
    let mut all_stats: Vec<PlayerStats> = vec![];
    for entry in fs::read_dir(input_path)? {
        let entry = entry?;
        let file_path: PathBuf = entry.path();
        if file_path.is_dir() { continue; }
        if !file_path.to_string_lossy().ends_with(".replay") { continue; }
        
        let replay: Replay = parse_replay(&file_path)?;
        let player_stats_prop = get_player_stats_property(&replay)?;
        let winning_team = get_winning_team(&replay)?;
        let stats = get_stats_from_player_stats(player_stats_prop, winning_team);
        for stat in stats.iter() {
            all_stats.push(stat.clone());
        }
        for _ in 0..(6 - stats.len()) {
            all_stats.push(PlayerStats::default());
        }
        println!(
            "Done reading {}",
            file_path.file_name()
                .ok_or_else(|| Error::new(
                        ErrorKind::Other,
                        "Failed to read file name"))?
                .to_string_lossy());
    }

    let file_name: String = prompt_for_user_input("What do you want the output file to be called?");
    output_path.push(file_name);
    output_path.set_extension("csv".to_string());
    write_csv(all_stats, output_path)?;
    Ok(())
}

fn main() {
    match run() {
        Err(error) => {
            println!("{}", error);
            prompt_for_user_input("Press 'Enter' to quit...");
        },
        Ok(_) => (),
    };
}
