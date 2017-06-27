import json, os, sys, subprocess

config_path = 'deps.json'

# init
print '> Deps fetcher 1.0'
if not os.path.exists(config_path):
	sys.exit('! No config found ! Aborting ...')

# parse config
config_file = open('deps.json', 'r')
config = json.loads(config_file.read())
config_file.close()

# create dir
deps_path = os.path.abspath(config["path"])
print '> Installing dependencies in ' + deps_path + ' ...'
if not os.path.exists(deps_path):
    os.makedirs(deps_path)

# clone packages (assume all git for now)
for package in config["packages"]:
	name = package["name"]
	origin = package["origin"]
	version = package["version"]

	# init repo
	repo_dir = os.path.join(deps_path, name)
	if not os.path.exists(repo_dir):
		os.makedirs(repo_dir)
		subprocess.call(['git', 'init', repo_dir])
		subprocess.call(['git', 'remote', 'add', 'origin', origin], cwd=repo_dir)
		subprocess.call(['git', 'fetch'], cwd=repo_dir)
		subprocess.call(['git', 'checkout', version], cwd=repo_dir)
	else:
		subprocess.call(['git', 'fetch'], cwd=repo_dir)
		subprocess.call(['git', 'checkout', version], cwd=repo_dir)
