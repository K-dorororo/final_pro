const express = require('express');
const cors = require('cors');
const app = express();
const port = 5000;

// CORS 설정
app.use(cors());

app.get('/api/data', (req, res) => {
  // 예제 데이터
  res.json({ temperature: 25, humidity: 60 });
});

app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});
