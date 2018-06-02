const {app, BrowserWindow, Menu} = require('electron');

function createWindow() {
	if (window) {
		return;
	}

	window = new BrowserWindow({width: 960, height: 562});
	window.loadFile('views/index.html');
	window.on('closed', () => {
		window = null;
	});
}

app.on('ready', () => {
	createWindow();
	Menu.setApplicationMenu(require('./menu'));
});

app.on('activate', createWindow);
app.on('window-all-closed', () => {
	if (process.platform !== 'darwin') {
		app.quit();
	}
});

let window;