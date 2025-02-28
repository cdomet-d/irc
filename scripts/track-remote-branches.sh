git fetch --all --prune
git branch -vv | grep ': gone]' | awk '{print $1}' | xargs git branch -d

git branch -r | grep -v '\->' | sed "s,\x1B\[[0-9;]*[a-zA-Z],,g" | while read remote; do
    local_branch="${remote#origin/}"
    if ! git branch --list "$local_branch" | grep -q "$local_branch"; then
        git branch --track "$local_branch" "$remote"
        echo "Created tracking branch: $local_branch"
		git pull
    else
        echo "Tracking branch already exists: $local_branch"
		git pull
    fi
done