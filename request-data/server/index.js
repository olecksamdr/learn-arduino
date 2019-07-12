const express = require('express');
const morgan = require('morgan');

const app = express();

app.use(morgan('combined'));

app.get('/api', (req, res) =>res.json({
  lightThreshold: 800,
  wetThreshold: 60,
  timeForPomp: 20000,
  syncInterval: 20000
}));

app.listen(3000, () => console.log(`App listening on port 3000!`));