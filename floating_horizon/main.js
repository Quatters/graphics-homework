function Point(x, y, z) {
  this.x = x;
  this.y = y;
  this.z = z;
}

function clonePoint(ptr) {
  this.x = ptr.x;
  this.y = ptr.y;
  this.z = ptr.z;
}

let canvas;
let ctx;

let pointField = [];

let CenterOfCoords = new Point(800, 390, 0);

let moveByOfCase = [];
let startPointOfCase = [];
let endPointOfCase = [];

let scale = 50;

let horizonBuffHeight = [];
let horizonBuffLow = [];
let horizonBuffLeft = [];
let horizonBuffRight = [];

let InGradusAngles = {
  x: 0,
  y: 0,
  z: 0,
};

let angles = {
  x: 0,
  y: 0,
  z: 0,
};

function makeRealAngle() {
  angles.x = (InGradusAngles.x / 180) * Math.PI;
  angles.y = (InGradusAngles.y / 180) * Math.PI;
  angles.z = (InGradusAngles.z / 180) * Math.PI;
}

function fillHorizonBuffs() {
  for (let i = 0; i <= canvas.height; i += 1) {
    horizonBuffHeight[i] = 0;
    horizonBuffLow[i] = canvas.height;
    horizonBuffLeft[i] = canvas.width;
    horizonBuffRight[i] = 0;
  }
}

function rotatePointByX(Pnt) {
  let tmp = new clonePoint(Pnt);
  Pnt.y = Math.cos(angles.x) * tmp.y + Math.sin(angles.x) * tmp.z;
  Pnt.z = -Math.sin(angles.x) * tmp.y + Math.cos(angles.x) * tmp.z;
}

function rotatePointByY(Pnt) {
  let tmp = new clonePoint(Pnt);
  Pnt.x = Math.cos(angles.y) * tmp.x - Math.sin(angles.y) * tmp.z;
  Pnt.z = Math.sin(angles.y) * tmp.x + Math.cos(angles.y) * tmp.z;
}

function rotatePointByZ(Pnt) {
  let tmp = new clonePoint(Pnt);
  Pnt.x = Math.cos(angles.z) * tmp.x + Math.sin(angles.z) * tmp.y;
  Pnt.y = -Math.sin(angles.z) * tmp.x + Math.cos(angles.z) * tmp.y;
}

function MovePointToNewCenter(Pnt) {
  Pnt.x += CenterOfCoords.x;
  Pnt.y += CenterOfCoords.y;
  Pnt.z += CenterOfCoords.z;
}

function expandPoint(Pnt) {
  Pnt.x *= scale;
  Pnt.y *= scale;
  Pnt.z *= scale;
}

function fullRotation(Pnt) {
  rotatePointByX(Pnt);
  rotatePointByY(Pnt);
  rotatePointByZ(Pnt);
}

function doNesRotationAndMovesAndInvertY(Pnt, show) {
  let tmp = new clonePoint(Pnt);
  tmp.y = -tmp.y;

  rotatePointByX(tmp);
  rotatePointByY(tmp);
  rotatePointByZ(tmp);

  expandPoint(tmp);

  MovePointToNewCenter(tmp);

  return new clonePoint(tmp);
}

function isPointCorrect(Pnt, isFirst, prevPnt) {
  let pp = Pnt.x !== NaN && Pnt.y !== NaN && Pnt.z !== NaN ? true : false;
  let correct = false;

  let x = Math.round(Pnt.x);
  let y = Pnt.y;

  if (horizonBuffHeight[x] < y) {
    correct = true;
    horizonBuffHeight[x] = y;
  }

  if (horizonBuffLow[x] > y) {
    correct = true;
    horizonBuffLow[x] = y;
  }

  y = Math.round(Pnt.y);
  x = Pnt.x;

  if (horizonBuffLeft[y] > x) {
    horizonBuffLeft[y] = x;
    correct = true;
  }

  if (horizonBuffRight[y] < x) {
    horizonBuffRight[y] = x;
    correct = true;
  }

  if (correct) {
    if (isFirst === false) {
      let dx = (-Pnt.x + prevPnt.x) / 20;
      let dy = (-Pnt.y + prevPnt.y) / 20;

      x = Pnt.x;
      y = Pnt.y;

      while (Math.abs(x - prevPnt.x) > 1e-6 && Math.abs(y - prevPnt.y) > 1e-6) {
        if (horizonBuffHeight[Math.round(x)] < y) {
          horizonBuffHeight[Math.round(x)] = y;
        }

        if (horizonBuffLow[Math.round(x)] > y) {
          horizonBuffLow[Math.round(x)] = y;
        }

        if (horizonBuffLeft[Math.round(y)] > x) {
          horizonBuffLeft[Math.round(y)] = x;
        }

        if (horizonBuffRight[Math.round(y)] < x) {
          horizonBuffRight[Math.round(y)] = x;
        }

        x += dx;
        y += dy;
      }
    }
  }

  return pp && correct;
}

function drawPoint(Pnt) {
  let halfSize = 5;
  ctx.fillRect(
    Math.round(Pnt.x) - halfSize,
    Math.round(Pnt.y) - halfSize,
    2 + halfSize,
    2 + halfSize
  );
}

function drawLines(Pnt) {
  ctx.lineTo(Pnt.x, Pnt.y);
}

function fillPointField() {
  let i = 0,
    j = 0;

  for (let x = -5; x <= 5; x += 0.1, i += 1) {
    j = 0;
    let tmp = [];
    for (let y = -5; y <= 5; y += 0.1, j += 1) {
      tmp[j] = new Point(x, y, Math.sin(x + y) / (x + y));
    }
    pointField.push(tmp);
  }
}

function whichIsCloser() {
  let z = doNesRotationAndMovesAndInvertY(pointField[0][0]).z;
  let cnt = 0;
  let a, b, tmp;

  a = 0;
  b = pointField[0].length - 1;
  tmp = doNesRotationAndMovesAndInvertY(pointField[a][b]);
  if (z < tmp.z) {
    z = tmp.z;
    cnt = 1;
  }

  a = pointField.length - 1;
  tmp = doNesRotationAndMovesAndInvertY(pointField[a][b]);
  if (z < tmp.z) {
    z = tmp.z;
    cnt = 3;
  }

  a = pointField.length - 1;
  b = 0;

  tmp = doNesRotationAndMovesAndInvertY(pointField[a][b]);
  if (z < tmp.z) {
    z = tmp.z;
    cnt = 2;
  }

  return cnt;
}

function draw() {
  let Case = whichIsCloser();

  let start = startPointOfCase[Case];
  let end = endPointOfCase[Case];
  let moveBy = moveByOfCase[Case];

  fillHorizonBuffs();

  for (let i = start.x; i != end.x; i += moveBy.x) {
    ctx.beginPath();
    let prev = new clonePoint(start);
    let isFirst = true;

    for (let j = start.y; j != end.y; j += moveBy.y) {
      let tmp = new clonePoint(pointField[i][j]);
      let point = doNesRotationAndMovesAndInvertY(tmp);

      if ((i % 4) % 3 === 0) ctx.strokeStyle = 'red';
      else ctx.strokeStyle = 'blue';

      if (isFirst) {
        ctx.moveTo(point.x, point.y);
        prev = point;
        isFirst = false;
      }

      if (isPointCorrect(point, isFirst, prev) === true) {
        ctx.lineTo(point.x, point.y);
        isFirst = false;
      } else {
        ctx.stroke();
        ctx.closePath();
        ctx.beginPath();
      }
      prev = point;
    }

    ctx.stroke();
    ctx.closePath();
  }
}

function clearScreen() {
  let tmp = ctx.fillStyle;
  ctx.fillStyle = 'white';
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = tmp;
}

let isListening = false;
let mouseStartX, mouseStartY;

function addEventsListeners() {
  canvas.addEventListener('mousedown', function (event) {
    mouseStartX = event.pageX;
    mouseStartY = event.pageY;
    isListening = true;
  });

  canvas.addEventListener('mouseup', function (event) {
    isListening = false;
  });

  canvas.addEventListener('mousemove', function (event) {
    if (isListening === true) {
      InGradusAngles.x += (mouseStartY - event.pageY) / 10;
      InGradusAngles.y += (mouseStartX - event.pageX) / 10;
      mouseStartX = event.pageX;
      mouseStartY = event.pageY;
      makeRealAngle();
      clearScreen();
      draw();
    }
  });
}

function init() {
  canvas = document.getElementById('paint');
  ctx = canvas.getContext('2d');

  fillPointField();

  moveByOfCase.push(new Point(1, 1, 0));
  moveByOfCase.push(new Point(1, -1, 0));
  moveByOfCase.push(new Point(-1, 1, 0));
  moveByOfCase.push(new Point(-1, -1, 0));

  startPointOfCase.push(new Point(0, 0, 0));
  startPointOfCase.push(new Point(0, pointField[0].length - 1, 0));
  startPointOfCase.push(new Point(pointField.length - 1, 0, 0));
  startPointOfCase.push(
    new Point(
      pointField.length - 1,
      pointField[pointField.length - 1].length - 1,
      0
    )
  );

  endPointOfCase.push(
    new Point(
      pointField.length - 1,
      pointField[pointField.length - 1].length - 1,
      0
    )
  );
  endPointOfCase.push(new Point(pointField.length - 1, 0, 0));
  endPointOfCase.push(new Point(0, pointField[0].length - 1, 0));
  endPointOfCase.push(new Point(0, 0, 0));

  addEventsListeners();

  ctx.fillStyle = 'white';
  clearScreen();

  makeRealAngle();
}

function Init() {
  init();
  draw();
}
