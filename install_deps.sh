#!/bin/bash

# Function declared with round parens is exectued in a subshell
function install_git_repo() (
	# Fetch the project
	git clone -v "$2" "$1"
	cd "$1"
	# Build
	make
	# Install
	make install
)

function clean_git_repo() {
	# Delete the repo
	rm -rfv "$1"
}


install_git_repo log 'https://github.com/Moonstroke/C-log.h'
clean_git_repo log
