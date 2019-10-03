extern crate boxcars;
extern crate dirs;
extern crate serde;

use boxcars::{ParseError, Replay, HeaderProp};
use serde_json;

use std::env;
use std::error;
use std::fs;
use std::io::{self, stdin, Read};
use std::path::*;
use std::string::*;

#[derive(Default)]
struct PlayerStats {
    name: String,
    platform: String,
    platform_id: String,
    mvp: bool,
    points: u32,
    goals: u16,
    assists: u16,
    saves: u16,
    shots: u16
}

fn prompt_for_user_input(prompt: &str) -> String {
    println!("{}", prompt);
    let mut input = String::new();
    stdin().read_line(&mut input).unwrap();
    input
}

fn read_path_input(prompt: &str) -> Result<PathBuf, String> {
    let input = prompt_for_user_input(prompt);
    let raw_path = PathBuf::from(input.trim_start().trim_end());
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

fn get_player_stats_property(replay: Replay) -> Option<HeaderProp> {
    for property in replay.properties {
        if property.0 == "PlayerStats" {
            return Some(property.1);
        }
    }
    None
}

fn make_player_stats(props: Vec<(String, HeaderProp)>) -> PlayerStats {
    let player = PlayerStats::default();
    for prop in props {
        let id = prop.0;
        let val = prop.1;
        match id.as_ref() {
            "Name"     => if let HeaderProp::Str(s) = val { player.name = s },
            "Platform" => if let HeaderProp::Str(s) = val { player.platform = s },
            "OnlineID" => if let HeaderProp::Str(s) = val { player.platform_id = s },
        }
    }
    player
}

fn get_stats_from_player_stats(replay_stats: HeaderProp) -> Vec<PlayerStats> {
    let stats = Vec::new();
    if let HeaderProp::Array(values) = replay_stats {
        for player_info in values {
            let player_stats = make_player_stats(values);
            stats.push(player_stats);
        }
    }
    stats
}

fn run() -> Result<(), Box<dyn error::Error>> {
    let args: Vec<String> = env::args().collect();
    println!("{:?}", args);
    let input_path: PathBuf = read_path_input("What is the path to the replay file directory")?;
    let output_path: PathBuf = read_path_input("What is the path to the output directory")?;
    for entry in fs::read_dir(input_path)? {
        let entry = entry?;
        let file_path: PathBuf = entry.path();
        if file_path.is_dir() { continue; }
        if !file_path.to_string_lossy().ends_with(".replay") { continue; }
        let replay: Replay = parse_replay(&file_path)?;
        println!("{}", file_path.to_string_lossy());
    }
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
