import requests
import base64
from collections import defaultdict
import os

def get_repo_info(username, repo_name, branch='main', token=None):
    # URL to get the repository details
    repo_url = f"https://api.github.com/repos/{username}/{repo_name}"
    
    # URL to get the repository tree
    tree_url = f"https://api.github.com/repos/{username}/{repo_name}/git/trees/{branch}?recursive=1"

    # Set up authentication headers
    headers = {}
    if token:
        headers['Authorization'] = f'token {token}'

    # Get repository details
    repo_response = requests.get(repo_url, headers=headers)
    if repo_response.status_code != 200:
        print(f"Failed to retrieve repository details: {repo_response.status_code}")
        return

    repo_data = repo_response.json()
    
    # Gather statistics
    stats = []
    stats.append(f"Repository: {repo_data['full_name']}")
    stats.append(f"Description: {repo_data['description']}")
    stats.append(f"Default Branch: {repo_data['default_branch']}")
    stats.append(f"Created At: {repo_data['created_at']}")
    stats.append(f"Updated At: {repo_data['updated_at']}")
    stats.append(f"Stars: {repo_data['stargazers_count']}")
    stats.append(f"Forks: {repo_data['forks_count']}")
    stats.append(f"Language: {repo_data['language']}\n")

    # Get the repository file tree
    tree_response = requests.get(tree_url, headers=headers)
    if tree_response.status_code != 200:
        print(f"Failed to retrieve repository tree: {tree_response.status_code}")
        return

    data = tree_response.json()

    total_chars = 0
    total_lines = 0
    file_count = 0
    dir_count = 0
    file_type_counts = defaultdict(lambda: {'chars': 0, 'lines': 0})

    # Allowed file types for a C project
    allowed_file_extensions = ['c', 'h']

    # Iterate through the items in the repository tree
    for item in data['tree']:
        if item['type'] == 'blob':  # Only process files
            file_url = item['url']
            file_response = requests.get(file_url, headers=headers)

            if file_response.status_code == 200:
                file_content = file_response.json()['content']
                decoded_content = base64.b64decode(file_content).decode('utf-8', errors='ignore')
                
                # Count characters and lines
                chars_count = len(decoded_content)
                lines_count = decoded_content.count('\n') + 1  # Add 1 for the last line if not newline-terminated

                # Get the file extension
                file_name = item['path']
                extension = file_name.split('.')[-1] if '.' in file_name else 'unknown'

                # Only count allowed file types
                if extension in allowed_file_extensions:
                    total_chars += chars_count
                    total_lines += lines_count
                    file_count += 1
                    file_type_counts[extension]['chars'] += chars_count
                    file_type_counts[extension]['lines'] += lines_count

        elif item['type'] == 'tree':  # Count directories
            dir_count += 1

    # Prepare to write the total information to README.md
    output = f"\nTotal Files: {file_count}\n"
    output += f"Total Directories: {dir_count}\n"
    output += f"Total Characters in C Files: {total_chars}\n"
    output += f"Total Lines in C Files: {total_lines}\n\n"
    output += "Character and line count by file type:\n"
    for ext, counts in file_type_counts.items():
        output += f"{ext}: Characters = {counts['chars']}, Lines = {counts['lines']}\n"

    # Write output to stats.txt or README.md
    with open('stats.txt', 'w') as stats_file:
        stats_file.write(output)

# Replace these with your actual values
username = "obamamen"  # Your GitHub username
repo_name = "CLI_RPG"  # Your repository name
branch = "main"  # The branch to analyze
token = os.environ.get('GITHUB_TOKEN')  # Use GitHub token from environment variable

get_repo_info(username, repo_name, branch, token)
