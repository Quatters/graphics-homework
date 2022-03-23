const canvas = document.querySelector('#canvas');
const ctx = canvas.getContext('2d');

ctx.translate(canvas.width / 2, canvas.height / 2);

drawLine(0);

setInterval(() => {
  clear();
  const angle = (Math.random() * 2 - 1) * Math.PI;
  drawLine(angle);
}, 1000);

function clear() {
  ctx.clearRect(
    -canvas.width / 2,
    -canvas.height / 2,
    canvas.width,
    canvas.height
  );
}

function drawLine(angle) {
  ctx.beginPath();
  ctx.moveTo(0, 0);
  ctx.lineTo(Math.cos(angle) * 200, Math.sin(angle) * 200);
  ctx.stroke();
}
