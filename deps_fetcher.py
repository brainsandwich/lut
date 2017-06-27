import json, os, sys, subprocess

def log(msg):
	print msg
	sys.stdout.flush()

config_path = 'deps.json'

# init
log('> Deps fetcher 1.0')

if not os.path.exists(config_path):
	sys.exit('! No config found ! Aborting ...')

# parse config
config_file = open('deps.json', 'r')
config = json.loads(config_file.read())
config_file.close()

# create dir
deps_path = os.path.abspath(config['path'])
log('> Installing dependencies in ' + deps_path + ' ...')
if not os.path.exists(deps_path):
    os.makedirs(deps_path)

# clone packages (assume all git for now)
for package in config['packages']:
	name = package['name']
	log('> Fetching package ' + name)

	origin = package['origin']
	version = package['version'] if 'version' in package else ''
	branch = package['branch'] if 'branch' in package else ''

	# init repo
	repo_dir = os.path.join(deps_path, name)
	if not os.path.exists(repo_dir):
		os.makedirs(repo_dir)
		subprocess.call(['git', 'init', repo_dir])
		subprocess.call(['git', 'remote', 'add', 'origin', origin], cwd=repo_dir)
		subprocess.call(['git', 'checkout', '-b', 'target'], cwd=repo_dir)

	# fetch branch / version
	subprocess.call(['git', 'fetch'], cwd=repo_dir)
	if version != '':
		subprocess.call(['git', 'reset', '--hard', version], cwd=repo_dir)
	else:
		subprocess.call(['git', 'reset', '--hard', 'origin/' + branch], cwd=repo_dir)
