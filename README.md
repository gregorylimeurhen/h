# h

A minimal program for daily tasks on MacOS.

## Installation

Clone repository.

Run command:
```sh
cd h
install h /usr/local/bin
```

## Usage

Run command:
```sh
h
```

Use Up or Down to move, and ENTER to select option:
```
hello! >w<

  [*] clone
  [ ] ship
  [ ] exit
```

### `clone`

Enter input:
```
what to clone? >w<

  owner/project: 
```

Input `foo/bar` runs command:
```sh
git clone https://github.com/foo/bar
```

Input `foo` runs command:
```sh
git clone "$(curl -s "https://api.github.com/search/repositories?q=foo&per_page=1" | jq -r ".items[0].html_url")"
```

### `ship`

Runs commands:
```sh
git add .
git commit --allow-empty-message --no-edit
git push
```

### `exit`

Runs command:
```sh
exit
```
