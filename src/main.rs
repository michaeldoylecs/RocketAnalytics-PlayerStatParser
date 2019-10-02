extern crate boxcars;
extern crate dirs;

use std::env;
use std::fs;
use std::io::{stdin};
use std::path::*;
use std::string::*;

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

fn run() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = env::args().collect();
    println!("{:?}", args);
    let input_path: PathBuf = read_path_input("What is the path to the replay file directory")?;
    let output_path: PathBuf = read_path_input("What is the path to the output directory")?;
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
