const http = require('http');
const fs = require('fs');
const exec = require('child_process').exec;
const {remote} = require('electron');
const settings = require('electron-settings');

const downloadUrl = 'http://localhost:5555/download/' + process.platform;
const delivery = '/tmp/wornite-' + process.platform + '.tar.gz';

function start(done) {
	remote.BrowserWindow.getFocusedWindow().minimize();
	exec('open /Applications/Worms.app', done);
}

function download(version, info, reject, callback) {
	http.get(downloadUrl).on('response', res => {
		console.log(res);
		const file = fs.createWriteStream(delivery);
		let downloaded = 0;

		res.on('data', chunk => {
			file.write(chunk);
			downloaded += chunk.length;
			info({
				status: `Downloading update... (${((version.size - downloaded) / 1024 / 1024).toFixed(0)} Mb)`,
				progress: (downloaded / version.size * 86).toFixed(0),
				ready: false
			});
		}).on('end', () => {
			file.end();
			callback();
		}).on('error', reject);
	}).on('error', reject);
}

function update(version, info) {
	return new Promise((resolve, reject) => {
		download(version, info, reject, () => {
			info({
				status: `Installing update...`,
				ready: false
			});

			exec(`tar xzf ${delivery}`, () => {
				const installers = {
					darwin: (done) => exec('cp -r /tmp/bin/darwin/Worms.app /Applications', done)
				};

				const installer = installers[process.platform];
				if (typeof installer !== 'function') {
					return reject();
				}

				installer((err, stdout, stderr) => {
					if (err) {
						console.log(err, stderr);
						return reject();
					}

					settings.set('gameversion', version.version);
					resolve();
				});
			});
		});
	});
}

function validate(version) {
	return settings.get('gameversion') === version.version;
}

module.exports = {
	validate,
	update,
	start
};