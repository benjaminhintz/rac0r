// var $ = function(id) {
// 	return document.getElementById(id);
// };

Number.prototype.mod = function(n) {
	return ((this%n)+n)%n;
};

var deg2rad = function(deg) {
	return deg * Math.PI / 180;
};

var rad2deg = function(rad) {
 	return rad * 180 / Math.PI;
};

var clone = function(obj) {
    if (null == obj || "object" != typeof obj) return obj;
    var copy = obj.constructor();
    for (var attr in obj) {
    	if(typeof attr == "object") {
    		attr = clone(attr); 
    	}
        if (obj.hasOwnProperty(attr)) copy[attr] = obj[attr];
    }
    return copy;
}

var Editor = function(canvas) {
	this.canvas = canvas;
	this.canvas.setAttribute('width', 800);
	this.canvas.setAttribute('height', 480);
	this.context = canvas.getContext("2d");
	
	this.start = null;
	this.placeStart = false;
	this.placeStartDrag = {x: 0, y: 0, toX: 0, toY: 0};


	this.trackCount = 5;
	this.trackLength = 20;

	// this.start = new Track(100,100, new Vector(0,this.trackLength));

	this.trackComplete = false;

	this.strokeStyles = ["rgba(  0, 153, 204, .6)",
						 "rgba(102, 153,   0, .6)",
						 "rgba(153,  51, 204, .6)",
						 "rgba(255, 136,   0, .6)",
						 "rgba(204,   0,   0, .6)"];

	this.init();
};

Editor.prototype.getStrokeStyle = function(trackNumber) {
	return this.trackComplete ? this.strokeStyles[trackNumber] : "rgba(95,126,237,.5)";
};

Editor.prototype.init = function() {
	var self = this;

	this.canvas.addEventListener('mousedown', function(evt) {
		if(window.location.hash != '#load') {
			if(self.start === null && !self.placeStart) {
				self.placeStart = true;
				self.placeStartDrag.x = evt.offsetX;
				self.placeStartDrag.y = evt.offsetY;
				self.placeStartDrag.toX = evt.offsetX;
				self.placeStartDrag.toY = evt.offsetY;
			}

			self.repaint();
		}
	});

	this.canvas.addEventListener('mousemove', function(evt) {
		if(self.placeStart) {
			self.placeStartDrag.toX = evt.offsetX;
			self.placeStartDrag.toY = evt.offsetY;

			var av = new Vector(10,0);
			var angle_cos = Math.acos(av.angle(self.getStartDirectionVector()));

			self.repaint();
		}

	});

	this.canvas.addEventListener('mouseup', function(evt) {
		if(self.placeStart) {

			var startVector = new Vector(self.placeStartDrag.x, self.placeStartDrag.y);
			var directionVector = self.getStartDirectionVector();

			if(!startVector.equals(directionVector) && !isNaN(directionVector.x)) {
				self.placeStart = false;

				// neuen track anlegen
				var t = new Track(startVector.x, startVector.y, directionVector);
				self.start = t;
			}
		}
		self.repaint();
	});

	document.body.addEventListener('keyup', function(evt) {
		if(evt.which == 27) {
			$('savebox').className ="";
			$('loadbox').className ="";
			window.location.hash = "#";
		}

		if(self.start !== null) {
			if(self.start.mPrevious == null || evt.keyIdentifier == 'Down') {
				switch(evt.keyIdentifier) {
					case 'Up':
						self.appendTrack();
						break;
					case 'Left':
						self.appendCurveLeft(!evt.shiftKey);
						break;
					case 'Right':
						self.appendCurveRight(!evt.shiftKey);
						break;
					case 'Down':
						self.removeLastTrack();
						break;
				}
			} else {
				if(self.start.mPrevious != null && window.location.hash != '#load' && window.location.hash != '#save') {
					alert('Strecke schon fertiggestellt.');
				}
			}

			self.repaint();
		} else {
			if(self.start == null && (evt.keyIdentifier == 'Up' || evt.keyIdentifier == 'Left' || evt.keyIdentifier == 'Right' || evt.keyIdentifier == 'Down')) {
				alert('Kein Start');
			}
		}
		return true;
	});

	$('save').addEvent('click', function() {
		if(!self.trackComplete) {
			if(!confirm("Strecke nicht vollständig. Trotzdem speichern?")) {
				window.location.hash = '#';
				return;
			}
		}

		self.save();
	});

	$('load').addEvent('click', function() {
		if(window.location.hash == '#load') {
			setTimeout(function() {
				$('loadbox').removeClass('visible');
				window.location.hash = "#";
			}, 50);
		} else {
			self.load();
		}
	});

	// $('save').addEventListener('click', function() {
	// 	text = "";
	// 	if(self.trackComplete) {
	// 		text = self.save();
	// 		var box = $('savebox');
	// 		box.className = "visible";
	// 		box.innerHTML = text;
	// 	} else {
	// 		if(confirm("Strecke nicht vollständig. Trotzdem speichern?")) {
	// 			text = self.save();
	// 			var box = $('savebox');
	// 			box.className = "visible";
	// 			box.innerHTML = text;
	// 		} else {
	// 			window.location.hash = "#";
	// 		}
	// 	}
	// });


	// $('load').addEventListener('click', function() {
	// 	var box = $('loadbox');
	// 	box.className = "visible";
	// });

	// document.body.addEventListener('click', function() {

	// 	if(window.location.hash == "#load" && $('loadbox').className == "visible") {
	// 		window.location.hash = "#";
	// 		if($('loadtext').value.length > 0) {
	// 			$('loadbox').className = "";
	// 			self.load($('loadtext').value);
	// 		}
	// 	}
	// });

	$('reset').addEvent('click', function() {
		setTimeout(function() {
			if(window.location.hash == '#reset') {
				if(confirm('Strecke wirklich zuruecksetzen?')) {
					self.start = null;
					self.trackComplete = false;
					self.repaint();

				}
				window.location.hash='';	
			}
		}, 50);
	});

};

Editor.prototype.save = function() {
	var text = "";
	var t = this.start;
	do {
		text += t.toString() + "\n";
		t = t.next();
	} while(t != null && t != this.start);
	track = text + (this.trackComplete ? "c" : "nc");

	img = this.canvas.toDataURL();

	req = new Request({
		url: 'save.php',
		method: 'post',
		onComplete: function(e) {
			if(parseInt(e) == 1) {
				alert('Gespeichert.');
			} else {
				alert('Konnte nicht gespeichert werden');
			}
		}
	});

	req.send('track=' + encodeURI(track) + "&image=" + img);
	window.location.hash = '#';
	
};

Editor.prototype.load = function(track) {

	var self = this;
	if(track === undefined && track == null) {
		req = new Request({
			url: 'load.php',
			method: 'get',
			onComplete: function(e) {
				eval("content = " + e + ";");
				self.showTrackList(content);
				// console.log(content);
				//$('loadbox').addClass('visible');
			}
		});
		req.send();
	} else {
		req = new Request({
			url: 'load.php',
			method: 'get',
			onComplete: function(e) {
				self.loadTrack(e);
			}
		});
		req.send('track=' + track);
	}		
	window.location.hash = '#';
};

Editor.prototype.showTrackList = function(trackList) {
	list = $('trackList');
	list.empty();
	var self = this;
	for(var i = 0; i < trackList.length; i++) {
		(function(id) {
			
			li = new Element('li', {});
			img = new Element('img', {src: trackList[id].image});
			li.addEvent('click', function() {
				self.load(trackList[id].track);
				$('loadbox').removeClass('visible');
			});
			img.inject(li);
			li.inject(list);
		})(i);
		
	}
	$('loadbox').addClass('visible');
};

Editor.prototype.loadTrack = function(trackText) {

	
	var lines = trackText.split("\n");

	var trackArray = [];
	for(var i = 0; i < lines.length-1; i++) {
		var line = lines[i];
		var parts = line.split(" ");
		if(parts.length > 0) {
			var t = parts[0];
			var x = parseFloat(parts[1]);
			var y = parseFloat(parts[2]);
			var dx = parseFloat(parts[3]);
			var dy = parseFloat(parts[4]);

			var track = new Track(x,y, new Vector(dx, dy));
			switch(t) {
				case 'l':
					track.mIsCurve = true;
					track.mCurveAngle = -45;
					break;
				case 'll':
					track.mIsCurve = true;
					track.mCurveAngle = -90;
					break;
				case 'r':
					track.mIsCurve = true;
					track.mCurveAngle = 45;
					break;
				case 'rr':
					track.mIsCurve = true;
					track.mCurveAngle = 90;
					break;
				default:
					break;
			}

			if(i > 0) {
				track.mPrevious = trackArray[i-1];
				trackArray[i-1].mNext = track;
			}

			if(i == lines.length -2 && lines[lines.length-1] == "c") {
				track.mNext = trackArray[0];
				trackArray[0].mPrevious = track;
				this.trackComplete = true;
			}

			trackArray.push(track);


		}
	}

	this.start = trackArray[0];
	this.repaint();
	
};

Editor.prototype.appendTrack = function() {
	// last track
	var last = this.start.getLast(this.start);

	// determine the new coords
	var v = last.getVector();
	var d = last.mIsCurve ? last.curveDirectionVector : last.directionVector;

	var n = last.mIsCurve ? last.curvePoint : v.add(d);
	var t = new Track(n.x, n.y, d);

	// chain them together
	last.mNext = t;
	t.mPrevious = last;

	if(t.equals(this.start)) {
		this.removeLastTrack();
		last.mNext = this.start;
		this.start.mPrevious = last;
		this.trackComplete = true;
	}

};

Editor.prototype.appendCurveLeft = function(ninety) {
	var last = this.start.getLast(this.start);

	var v = last.getVector();
	var d = last.mIsCurve ? last.curveDirectionVector : last.directionVector;
	var n = last.mIsCurve ? last.curvePoint : v.add(d);
	var t = new Track(n.x, n.y, d);

	t.mIsCurve = true;
	t.mCurveAngle = ninety ? -90 : -45;

	last.mNext = t;
	t.mPrevious = last;
};

Editor.prototype.appendCurveRight = function(ninety) {

	var last = this.start.getLast(this.start);

	var v = last.getVector();
	var d = last.mIsCurve ? last.curveDirectionVector : last.directionVector;
	var n = last.mIsCurve ? last.curvePoint : v.add(d);
	var t = new Track(n.x, n.y, d);

	t.mIsCurve = true;
	t.mCurveAngle = ninety ? 90: 45;

	last.mNext = t;
	t.mPrevious = last;
};

Editor.prototype.removeLastTrack = function() {
	var last = this.start.getLast(this.start);
	
	if(this.start.mPrevious != null) {
		this.start.mPrevious.mNext = null;
		this.start.mPrevious = null;
		this.trackComplete = false;
		return ;
	}

	var p = last.mPrevious;
	if(p === null) {
		// wir haben den start, also start weg nehmen
		this.start = null;
		delete last;
		return;
	}

	p.mNext = null;
	delete last;
};

Editor.prototype.setStart = function(x, y) {
	console.log("x: " + x + " y: " + y);
	this.start = new Track(x, y);
};

Editor.prototype.paint = function() {
	this.drawGrid();
	if(this.placeStart) {
		// draw point where the start is 

		var directionVector = this.getStartDirectionVector();

		var x = this.placeStartDrag.x;
		var y = this.placeStartDrag.y;

		this.context.beginPath();
		this.context.fillStyle = "rgba(95,126,237,.5)";
		this.context.arc(x, y, 4, 0, 2*Math.PI);
		this.context.fill();

		this.context.beginPath();
		this.context.strokeStyle = "rgba(95,126,237,.25)";
		this.context.moveTo(x, y);
		this.context.lineWidth = 1;
		this.context.lineTo(x + directionVector.x, y + directionVector.y);
		this.context.stroke();
	} else {
		// track zeichnen
		if(this.start !== null) {
			var t = this.start;
			do {
				t.draw(this.context);
				t = t.next();
			} while(t !== null && t !== this.start);
		}
	}
};

Editor.prototype.drawGrid = function(){
	if(!this.trackComplete) {
		this.context.lineWidth = .5;
		this.context.strokeStyle = "rgba(255,255,255,.05)";
		
		for(var i = 0; i < this.canvas.width; i = i+10) {
			this.context.beginPath();
				this.context.moveTo(i+.5,0+.5);
				this.context.lineTo(i+.5,this.canvas.height+.5);
				this.context.stroke();
		}


		for(var i = 0; i < this.canvas.height; i+=10) {
			this.context.beginPath();
				this.context.moveTo(0+.5,i+.5);
				this.context.lineTo(this.canvas.width+.5,i+.5);
				this.context.stroke();
		}
	}
	
}

Editor.prototype.getStartDirectionVector = function() {
	var v1 = new Vector(this.placeStartDrag.x, this.placeStartDrag.y);
	var v2 = new Vector(this.placeStartDrag.toX, this.placeStartDrag.toY);
	var dir = v2.sub(v1);
	var diru = dir.unit();
	var directionVector = diru.mul(this.trackLength);
	return directionVector;
};

Editor.prototype.repaint = function() {
	this.clearCanvas();
	this.paint();
};

Editor.prototype.clearCanvas = function() {
	this.context.fillStyle = "rgba(16,16,16,1)";
	this.context.clearRect(0 ,0 ,this.canvas.width ,this.canvas.height);
	this.context.fillRect(0 ,0 ,this.canvas.width ,this.canvas.height);
};