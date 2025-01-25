repo forall -c '
author="@idtechproducts.com"
output_dir="/home/uqtony/idtech_commits_output"
mkdir -p $output_dir
git log --author="$author" --pretty=format:"%H" | while read commit_hash; do
    commit_info=$(git show --pretty=format:"%h %an %ad%n%n%s%n%n%b" --date=short "$commit_hash")
    project_path=$(echo $REPO_PATH | tr "/" "_")
    title=$(echo "${commit_info}"|sed -n "3p")
    file_name="$output_dir/${project_path}_${commit_hash}_${title}.txt"
    echo "$commit_info" > "$file_name"
    echo "Saved: $file_name"
done
'

