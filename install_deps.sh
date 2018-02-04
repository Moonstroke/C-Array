#!/bin/bash

# Function declared with round parens is exectued in a subshell
function install_git_repo() (
	# Fetch the project
	git clone --quiet "$2" "$1" &&
	cd "$1" &&
	# Build
	make &&
	# Install
	make install &&
	echo "Successfully installed \"$1\" from \"$2\""
)

function clean_git_repo() {
	# Delete the repo
	rm -rf "$1" &&
	echo "Removed clone repo \"$1\""
}


install_git_repo log 'https://github.com/Moonstroke/C-log.git'
clean_git_repo log
