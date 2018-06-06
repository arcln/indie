const jquery = require('jquery');
const Handlebars = require('handlebars');
const updater = require('./updater');

let lastFooter = {ready: 42};

module.exports = renderer = {
	render: function() {
		renderer.states.loading('Checking for available update...');

		jquery.ajax({
			url: 'http://localhost:5555/version/' + process.platform,
			type: 'get',
			error: function(XMLHttpRequest, textStatus, errorThrown) {
				renderer.states.error();
			},
			success: function(version) {
				if (updater.validate(version)) {
					renderer.states.ready();
				} else {
					updater.update(version, status => renderer.states.any(status))
						.then(() => renderer.states.ready())
						.catch(err => renderer.states.error());
				}
			}
		});
	},
	states: {
		any: function(context) {
			if (lastFooter.ready !== context.ready) {
				jquery('.footer').html(Handlebars.compile(jquery('#footer-template').html())(context));

				if (context.ready) {
					jquery('#play').on('click', () => {
						jquery('#play').removeClass('play-btn').addClass('play-btn-disabled');
						setTimeout(() => updater.start(() => jquery('#play').removeClass('play-btn-disabled').addClass('play-btn'), 200));
					});
				}
			}

			jquery('#progress').html(Handlebars.compile(jquery('#progress-bar-template').html())(context));
			jquery('#status').html(Handlebars.compile(jquery('#status-template').html())(context));

			lastFooter = context;
		},
		loading: function(status) {
			renderer.states.any({
				playBtnState: 'play-btn-disabled',
				status: status,
				ready: false
			});
		},
		ready: function() {
			renderer.states.any({
				status: '<span style="color: #52B788; margin-right: 7px">&check;</span> Ready to play',
				ready: true,
				playBtnState: 'play-btn'
			});
		},
		error: function() {
			renderer.states.any({
				playBtnState: 'play-btn-disabled',
				status: '<span style="color: red; margin-right: 7px">&#10005;</span> An unexpected error occured. Please try again later.',
				ready: true
			});
		}
	}
};

