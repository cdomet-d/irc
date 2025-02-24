#!/bin/bash

git fetch --all --prune

if git branch -vv | grep ': gone]'; then
	git branch -vv | grep ': gone]' | awk '{print $1}' | xargs git branch -d
fi

current_branch=$(git rev-parse --abbrev-ref HEAD)

git branch -r | grep -v '\->' | sed "s,\x1B\[[0-9;]*[a-zA-Z],,g" | while read remote; do
    local_branch="${remote#origin/}"
    if ! git branch --list "$local_branch" | grep -q "$local_branch"; then
        git branch --track "$local_branch" "$remote"
        echo "Created tracking branch: $local_branch"
    else
        echo "Tracking branch already exists: $local_branch"
    fi
    
	if git branch -vv | grep behind; then
		if git switch "$local_branch"; then
			git pull origin "$local_branch"
		else
			error="true"
			break
		fi
	fi
done

if [ "$error" == "true" ]; then
	echo "Please commit your current changes"
fi

git switch "$current_branch"