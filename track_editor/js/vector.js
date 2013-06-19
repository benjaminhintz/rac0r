var Vector = function(x, y) {
	this.x = x;
	this.y = y;
};

Vector.prototype.add = function(vec) {
	return new Vector(this.x + vec.x, this.y + vec.y);
};

Vector.prototype.sub = function(vec) {
	return new Vector(this.x - vec.x, this.y - vec.y);
};

Vector.prototype.skalar = function(vec) {
	return this.x*vec.x + this.y*vec.y;
};

Vector.prototype.length = function() {
	l = Math.sqrt( this.x * this.x + this.y * this.y);
	return l;
};

Vector.prototype.div = function(value) {
	v = new Vector(0,0);
	if(value > 0) {
		v.x = this.x/value;
		v.y = this.y/value;
	}
	return v;
};

Vector.prototype.mul = function(value) {
	x = this.x;
	y = this.y;

	v = new Vector(this.x * value, this.y * value);
	return v;
};

Vector.prototype.unit = function() {
	l = 1/this.length();

	v = new Vector(this.x, this.y);
	v = v.mul(l);
	return v;
}

Vector.prototype.angle = function(vec) {
	l1 = this.length();
	l2 = vec.length();
	cos = this.skalar(vec) / (l1*l2);
	return  cos;
};

Vector.prototype.clone = function() {
	return new Vector(this.x, this.y);
};

Vector.prototype.orthogonal = function() {
	v = new Vector(this.y, -this.x);
	return v;
};

Vector.prototype.toString = function() {
	return "x: " + (this.x.toFixed(5)) + " y:" + (this.y.toFixed(5)) + " length: " + this.length();
};

Vector.prototype.equals = function(vec) {
	//console.log(this.toString() + "\n" + vec.toString());

	if(this.x.toFixed(5) == -0.00000) this.x *= 0;
	if(this.y.toFixed(5) == -0.00000) this.y *= 0;

	return this.x.toFixed(5) == vec.x.toFixed(5) && this.y.toFixed(5) == vec.y.toFixed(5);
};

Vector.prototype.translate = function(x, y) {
	this.x += x;
	this.y += y;
};

Vector.prototype.translateV = function(vec) {
	this.x += vec.x;
	this.y += vec.y;
}

Vector.prototype.scale = function(factor) {
	len = this.length();
	vec = this.unit();
	vec2 = vec.mul(len * factor);
	return vec2;
};


Vector.prototype.rotate = function(deg) {
	px = this.x * Math.cos(deg2rad(deg)) - this.y * Math.sin(deg2rad(deg)); 
	py = this.x * Math.sin(deg2rad(deg)) + this.y * Math.cos(deg2rad(deg));
	this.x = px;
	this.y = py;

	return this;
};