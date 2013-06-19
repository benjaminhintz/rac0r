var Track = function(x, y, directionVector) {
	this.mNext = null;
	this.mPrevious = null;

	this.mIsCurve = false;
	this.mCurveAngle = 0;

	this.x = x;
	this.y = y;
	this.directionVector = directionVector;
	this.curveDirectionVector = null;
	this.curvePoint = null;

	this.factor = 1;
	this.trackLength = 20;
};

Track.prototype.next = function() {
	return this.mNext;
};

Track.prototype.prev = function() {
	return this.mPrev;
};

Track.prototype.getVector = function() {
	return new Vector(this.x, this.y);
};

Track.prototype.getLast = function(start) {
	while(this.mNext != null) {
		if(this == start && this.mPrevious !== null) {
			return this.mPrevious;
		}
		return this.mNext.getLast(start);
	}
	return this;
};

Track.prototype.draw = function(ctx) {



	// original vector
	var v_orig = this.getVector();


	// draw the orig vector
	if(!editor.trackComplete) {
		this.drawVector(ctx, v_orig);
	}

	if(this.mIsCurve) {



		var ortho = this.directionVector.orthogonal();
		var ortho_u = ortho.unit();
		

		var ortho_n = ortho_u.mul((this.directionVector.length()*1.5) * (this.mCurveAngle < 0 ? 1 : -1));
		var ortho_n2 = ortho_u.mul((this.directionVector.length()/2) * (this.mCurveAngle < 0 ? 1 : -1));

		// ortho_n is the curve center
		var innerRadius = this.directionVector.length() + (editor.trackComplete ? (this.directionVector.length()/2 - this.trackLength/2) : 0);
		var outerRadius = innerRadius + this.trackLength;

		// center;
		var c = v_orig.add(ortho_n);

		// this.drawVector(ctx, c);

		var av = new Vector(10,0);
		var angle_cos = Math.acos(av.angle(this.directionVector));

		var skalar = av.skalar(ortho);
		if(skalar > 0) angle_cos = -angle_cos;


		var c0 = this.mCurveAngle < 0 ? v_orig.sub(ortho_n2) : v_orig.add(ortho_n2);
		var c1 = c0.add(ortho);


		ctx.translate(v_orig.x + ortho_n.x, v_orig.y + ortho_n.y);
		ctx.rotate(-angle_cos);

		var tracks = editor.trackCount;
		if(!editor.trackComplete) {
			tracks = 2;
		}
		ctx.lineWidth=2*this.factor;

		// DO THE LOOP
		for(var i = 0; i < tracks; i++) {
			var part = 1;

			if(tracks > 1) {
				 var diff = this.mCurveAngle < 0 ? innerRadius - outerRadius : outerRadius - innerRadius;
				 var part = diff / (tracks-1) * i;
			}

			ctx.beginPath();
				ctx.strokeStyle = editor.getStrokeStyle(i);
				if(this.mCurveAngle < 0) {
					ctx.arc(0, 0, outerRadius + part, deg2rad(90), deg2rad(90+this.mCurveAngle), true);
				} else {
					ctx.arc(0, 0, innerRadius + part, deg2rad(360-90), deg2rad(360-90+this.mCurveAngle));
				}
				ctx.stroke();
			ctx.closePath();
		}

		ctx.rotate(angle_cos);
		ctx.translate(-(v_orig.x + ortho_n.x), -(v_orig.y + ortho_n.y));


		ctx.strokeStyle = "rgba(95,126,237,.5)";

		if(!editor.trackComplete) {
			ctx.beginPath();
				ctx.moveTo(c0.x, c0.y);
				ctx.lineTo(c1.x, c1.y);
				ctx.stroke();
			ctx.closePath();
		}

		if(!editor.trackComplete) {
			this.drawVector(ctx, c, 2);
		}

		vn = v_orig.sub(c.clone());
		vn.rotate(this.mCurveAngle);
		vnn = vn.add(c.clone());
		this.curvePoint = vnn;

		c0 = this.mCurveAngle < 0 ? vnn.sub(ortho_n2.rotate(this.mCurveAngle)) : vnn.add(ortho_n2.rotate(this.mCurveAngle)) ;
		c1 = c0.add(ortho.rotate(this.mCurveAngle));
		
		if(!editor.trackComplete) {
			ctx.beginPath();
				ctx.moveTo(c0.x, c0.y);
				ctx.lineTo(c1.x, c1.y);
				ctx.stroke();
			ctx.closePath();
		}

		vn = this.directionVector.clone();
		vnu = vn.unit();
		vnn = vn.rotate(this.mCurveAngle);
		this.curveDirectionVector = vnn;

	} else {

		// otho for the bounds
		var ortho = this.directionVector.orthogonal();
		var ortho_u = ortho.unit();
		var ortho_n = ortho_u.mul(this.trackLength/2);

		// bounds
		var c0 = v_orig.sub(ortho_n);
		var c1 = c0.add(this.directionVector);
		var c2 = c1.add(ortho);
		var c3 = c2.sub(this.directionVector);
		var bounds = [c0,c1,c2,c3];

		ctx.lineWidth=2*this.factor;

		// draw bounds
		if(!editor.trackComplete) {

			ctx.strokeStyle = "rgba(95,126,237,.5)";
			for(var i = 0; i < bounds.length; i++) {
				var prev = bounds[(i-1).mod(bounds.length)];
				var curr = bounds[i];
				ctx.beginPath();
					ctx.moveTo(prev.x, prev.y);
					ctx.lineTo(curr.x, curr.y);
					ctx.stroke();
				ctx.closePath();			
			}
		} else {


			var t = ortho_n.unit();


			for(var i = 0; i < editor.trackCount; i++) {
				var part = 1;
				if(editor.trackCount > 1) {
					 part = this.trackLength / (editor.trackCount-1) * i;
				}

				ctx.strokeStyle = editor.getStrokeStyle(i);

				tt = t.mul(part);
				t0 = c0.clone().add(tt);
				t1 = c1.clone().add(tt);

				ctx.beginPath();
					ctx.moveTo(t0.x, t0.y);
					ctx.lineTo(t1.x, t1.y);
					ctx.stroke();
				ctx.closePath();
			}
		}
	}
};


Track.prototype.drawVector = function(ctx, vec, radius) {
	ctx.beginPath();
		ctx.fillStyle = "rgba(95,126,237,.5)";
		ctx.arc(vec.x, vec.y, radius != null ? radius : 4, 0, deg2rad(360));
		ctx.fill();
	ctx.closePath();
};

Track.prototype.equals = function(track) {
	return this.getVector().equals(track.getVector()) && this.directionVector.equals(track.directionVector);
};

Track.prototype.toString = function() {

	var v,d,n;

	var type = this.mIsCurve ? (this.mCurveAngle < 0 ? ((this.mCurveAngle == -90) ? "ll" : "l" ) : ((this.mCurveAngle == 90) ? "rr" : "r" )) : "s";
	last = this.mPrevious;

	return type  + " " + this.x + " " + this.y + " " + this.directionVector.x + " " + this.directionVector.y;
};

Track.prototype.clone = function() {
	var cloned = new Track(this.x, this.y, this.directionVector.clone());
	cloned.mNext = null;
	cloned.mPrevious = null;

	cloned.mIsCurve = this.mIsCurve;
	cloned.mCurveAngle = this.mCurveAngle;

	if(this.curveDirectionVector != null) cloned.curveDirectionVector = this.curveDirectionVector.clone();
	if(this.curvePoint != null) cloned.curvePoint = this.curvePoint.clone();

	cloned.trackLength = this.trackLength;
	return cloned;
};

Track.prototype.setPosition = function(vector) {
	this.x = vector.x;
	this.y = vector.y;
}

Track.prototype.translate = function(x,y) {
	vec = this.getVector();
	vec.translate(x,y);
	this.setPosition(vec);
};

Track.prototype.scale = function(factor) {
	this.factor = 1;
	vec = this.getVector();
	scaled = vec.scale(factor);
	this.setPosition(scaled);

	//this.trackLength *= factor;
	dirVec = this.directionVector.scale(factor);
	this.directionVector = dirVec;
};