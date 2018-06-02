const app = require('express')();
const cors = require('cors');
const fs = require('fs');

const version = 'v0.3';
const delivery = platform => `dist/wornite-${platform}.tar.gz`;

app.use(cors());

app.get("/version/:platform", (req, res) => {
	res.status(200).send({
		version: version,
		size: fs.statSync(delivery(req.params.platform)).size
	});
});

app.get("/download/:platform", (req, res) => {
	fs.createReadStream(delivery(req.params.platform)).pipe(res);
});

app.listen(5555);