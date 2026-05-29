#!/bin/sh

down=$(printf "\033[B")
enter=$(printf "\r")
escape=$(printf "\033")
up=$(printf "\033[A")

selected=0
settings=$(stty -g)

num_options=5

newline() { printf "\r\n"; }
newscreen() { printf "\033[H\033[J"; }

hidecursor() { printf "\033[?25l"; }
showcursor() { printf "\033[?25h"; }

cleanup() {
	showcursor
	stty "$settings"
	newline
}

next_option() { selected=$(( (selected + 1) % num_options )); }
previous_option() { selected=$(( (selected + num_options - 1) % num_options )); }
option() {
	case "$1" in
		0) printf "clean disk" ;;
		1) printf "clone repo" ;;
		2) printf "ship repo" ;;
		3) printf "update h" ;;
		4) printf "quit h" ;;
	esac
}

trap cleanup EXIT
trap "exit" HUP TERM
stty raw -echo
hidecursor

while :
do
	# draw menu
	newscreen
	printf ">w<"
	newline
	newline
	index=0
	while [ "$index" -lt "$num_options" ]
	do
		bullet=" "
		[ "$index" -eq "$selected" ] && bullet="*"
		printf "  [%s] %s" "$bullet" "$(option "$index")"
		newline
		index=$((index + 1))
	done

	# read keypress
	keypress=$(dd bs=1 count=1 2>/dev/null)
	[ "$keypress" = "$escape" ] && keypress="$keypress$(dd bs=1 count=2 2>/dev/null)"

	# act on keypress
	case "$keypress" in
		"$up") previous_option ;;
		"$down") next_option ;;
		"$enter")
			cleanup
			case "$selected" in
				0)
					brew cleanup --prune=all
					npm cache clean --force
					set -- \
						"$HOME/.cargo/git" \
						"$HOME/.cargo/registry" \
						"$HOME/Library/Application Support/Code/Cache" \
						"$HOME/Library/Application Support/Code/CachedData" \
						"$HOME/Library/Application Support/Slack/Cache" \
						"$HOME/Library/Caches" \
						"$HOME/Library/Developer/Xcode/Archives" \
						"$HOME/Library/Developer/Xcode/DerivedData" \
						"$HOME/Library/Developer/Xcode/iOS DeviceSupport" \
						"$HOME/Library/Logs"
					du -sh "$@" 2>/dev/null | sort -hr
					while :
					do
						newline
						printf "owo"
						newline
						newline
						printf "  y/n: "
						IFS= read -r answer
						case "$answer" in
							y)
								rm -rf "$@"
								break
								;;
							n) exit ;;
						esac
					done
					;;
				1)
					while :
					do
						newscreen
						printf "owo"
						newline
						newline
						printf "  owner/project: "
						IFS= read -r repository
						[ -n "$repository" ] && break
					done
					case "$repository" in
						*/*) git clone "https://github.com/$repository" ;;
						*)
							api=https://api.github.com/search/repositories
							git clone "$(
								curl -s "$api?q=$repository&per_page=1" |
								jq -r ".items[0].html_url"
							)"
							;;
					esac
					;;
				2)
					git add .
					git commit --allow-empty-message --no-edit
					git push
					;;
				3)
					curl -fsSL "https://raw.githubusercontent.com/gregorylimeurhen/h/refs/heads/main/h" -o ./h
					install h /usr/local/bin
					;;
				4)
					printf ">w<"
					newline
					exit
					;;
			esac
			exit
			;;
	esac
done
