import React, { useEffect, useState } from 'react';
import './App.css';

const App = () => {
  const [data, setData] = useState({
    temperature: null,
    humidity: null,
  });
  const [error, setError] = useState(null);

  // 데이터 가져오기 함수
  const fetchData = async () => {
    try {
      const response = await fetch('http://192.168.0.6:5000/data'); // 서버 URL 확인
      if (!response.ok) {
        throw new Error('Network response was not ok');
      }
      const result = await response.json();
      setData(result);
      setError(null);
    } catch (error) {
      console.error('Error fetching data:', error);
      setError('Error fetching data');
    }
  };

  // 컴포넌트가 마운트될 때 데이터 가져오기
  useEffect(() => {
    fetchData();

    // 3초마다 데이터 갱신
    const intervalId = setInterval(() => {
      fetchData();
    }, 3000); // 3000ms = 3초

    // 컴포넌트 언마운트 시 인터벌 클리어
    return () => clearInterval(intervalId);
  }, []);

  return (
    <div className="app-container">
      <h1>MINI SMART FARM VIEWER</h1>
      {error && <p>{error}</p>}
      <div className="data-container">
        <div className="data-item temperature">
          <h2>온도</h2>
          <p>{data.temperature !== null ? `${data.temperature}°C` : '데이터 없음'}</p>
        </div>

        <div className="data-item humidity">
          <h2>습도</h2>
          <p>{data.humidity !== null ? `${data.humidity}%` : '데이터 없음'}</p>
        </div>
      </div>
    </div>
  );
};

export default App;
