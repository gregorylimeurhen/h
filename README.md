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

Use Up, Down, and/or Enter to select option:
```
>w<

  [*] clean disk
  [ ] clone repo
  [ ] ship repo
  [ ] update h
  [ ] quit h
```

### `clean disk`

Runs commands:
```sh
brew cleanup --prune=all
conda clean --all
npm cache clean --force
```

Runs commands:
```sh
paths=(
  "$HOME/.android/avd"
  "$HOME/.android/cache"
  "$HOME/.cache"
  "$HOME/.thumbnails"
  "$HOME/Library/Application Support/Code/Cache"
  "$HOME/Library/Application Support/Code/CachedData"
  "$HOME/Library/Application Support/Slack/Cache"
  "$HOME/Library/Developer/Xcode/Archives"
  "$HOME/Library/Developer/Xcode/DerivedData"
  "$HOME/Library/Developer/Xcode/iOS DeviceSupport"
)
du -sh "${paths[@]}" 2>/dev/null | sort -hr
```

Enter input:
```sh
owo

  y/n: 
```

Input `y` runs command:
```sh
rm -rf "${paths[@]}"
```

Input `n` runs command:
```sh
exit
```

### `clone repo`

Enter input:
```
owo

  owner/project: 
```

Input `foo/bar` runs command:
```sh
git clone https://github.com/foo/bar
```

Input `foo` runs command:
```sh
git clone "$(curl -s "https://api.github.com/search/repositories?q=foo&per_page=1" \
| jq -r ".items[0].html_url")"
```

### `ship repo`

Runs commands:
```sh
git add .
git commit --allow-empty-message --no-edit
git push
```

### `update h`

Runs commands:
```sh
curl -fsSL "https://raw.githubusercontent.com/gregorylimeurhen/h/refs/heads/main/h" -o ./h
install h /usr/local/bin
```

### `quit h`

Runs command:
```sh
exit
```
