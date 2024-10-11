const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 5000; // 하나의 포트로 통합

// CORS 설정
app.use(cors());

// body-parser 미들웨어 설정
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

// 센서 데이터 저장을 위한 객체
let sensorData = {
    temperature: null,
    humidity: null
};

// POST 요청 처리 (데이터 수신)
app.post('/data', (req, res) => {
    try {
        const { temperature, humidity } = req.body;
        console.log(`Received data - Temperature: ${temperature}, Humidity: ${humidity}`);
        
        // 수신한 데이터 저장
        sensorData.temperature = temperature;
        sensorData.humidity = humidity;
        
        res.status(200).json({ status: 'success', temperature, humidity });
    } catch (err) {
        next(err); // 오류 발생 시 오류 처리 미들웨어로 전달
    }
});

// GET 요청 처리 (데이터 제공)
app.get('/data', (req, res) => {
    try {
        res.json(sensorData);
    } catch (err) {
        next(err); // 오류 발생 시 오류 처리 미들웨어로 전달
    }
});

// 오류 처리 미들웨어
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send('Something broke!');
});

// 서버 실행
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
