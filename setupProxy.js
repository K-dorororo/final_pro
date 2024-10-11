const { createProxyMiddleware } = require('http-proxy-middleware');

module.exports = function(app) {
  app.use(
    createProxyMiddleware('/api', {
      target: 'http://203.237.153.31:5000',  // 서버의 주소와 포트
      changeOrigin: true,
      secure: false // HTTPS를 사용하는 경우 설정
    })
  );
};
