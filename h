#!/bin/sh

enter=$(printf "\r")
selected=0
settings=$(stty -g)

blankline() { printf "\r\n\r\n"; }
newline() { printf "\r\n"; }
newscreen() { printf "\033[H\033[J"; }

hidecursor() { printf "\033[?25l"; }
showcursor() { printf "\033[?25h"; }

cleanup() {
	showcursor
	stty "$settings"
}

next_option() { selected=$(( (selected + 1) % 3 )); }
previous_option() { selected=$(( (selected + 2) % 3 )); }

trap cleanup EXIT
trap "exit" HUP TERM
stty raw -echo
hidecursor

while :
do
	# draw menu
	newscreen
	printf "hello! >w<"
	blankline
	index=0
	for option in clone ship exit
	do
		bullet=" "
		[ "$index" -eq "$selected" ] && bullet="*"
		printf "  [%s] %s" "$bullet" "$option"
		newline
		index=$((index + 1))
	done
	newline

	# read keypress
	keypress=$(dd bs=1 count=1 2>/dev/null)

	# act on keypress
	case "$keypress" in
		w) previous_option ;;
		s) next_option ;;
		"$enter")
			cleanup
			newline

			case "$selected" in
				0)
					while :
					do
						newscreen
						printf "what to clone? >w<\n\n  owner/project: "
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
				1)
					git add .
					git commit --allow-empty-message --no-edit
					git push
					;;
				2) exit ;;
			esac
			exit
			;;
	esac
done
