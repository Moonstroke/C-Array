#!/bin/bash

# Functions declared with round parens are exectued in a subshell
function install_git_repo() (
	# Fetch the project
	git clone --quiet "$2" "$1" &&
	cd "$1" &&
	# Build
	make &&
	# Install
	sudo make install &&
	echo "Successfully installed \"$1\" from \"$2\""
)

function clean_git_repos() {
	# Delete the repo
	rm -rf "$@" &&
	echo "Removed cloned repos" "$@"
}


install_git_repo clog 'https://github.com/Moonstroke/Clog.git'
install_git_repo cute 'https://github.com/Moonstroke/CUTE.git'
clean_git_repos clog cute
