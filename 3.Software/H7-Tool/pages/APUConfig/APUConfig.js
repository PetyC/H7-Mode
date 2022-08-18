// pages/APUConfig/APUConfig.js
var util = require("../../utils/util.js");

var APUConfigStart = false;//是否在配网

var APUConfigconnectAPCount = 0;//连接热点的次数

var APUConfigSendUDPDataIntervalNumber = 0;//发送UDP数据的定时器编号

var APUConfigSendUDPDataCount = 0;//发送UDP数据的次数

var udp;

Page({

  /**
   * 页面的初始数据
   */
  data: {
    ssid: '',
    password: ''
  },
  // 获取路由器名称
  ssidInput: function (e) {
    this.data.ssid = e.detail.value;
  },
  // 获取输入密码 
  passwordInput: function (e) {
    this.data.password = e.detail.value;
  }, 
    /**
   * 成功连接热点
   */
  connectWifiSuccess: function(res)
  {
    var _this = this;
    udp = wx.createUDPSocket()//启用UDP
    udp.bind()

    wx.hideLoading();
    wx.showLoading({
      title: '正在绑定'
    })

    udp.onListening(function (res) {
      console.log('监听中...')
      console.log(res)
    })


    //定时1S发送一次UDP数据
    try { clearInterval(APUConfigSendUDPDataIntervalNumber); } catch (e) { }

    APUConfigSendUDPDataIntervalNumber = setInterval(
      function () {
        udp.send
          ({
            address: '192.168.4.1',
            port: 5556,
            message: "{\"ssid\":" + "\"" + _this.data.ssid + "\"" + ",\"pwd\":" + "\"" + _this.data.password + "\"" + "}\r\n"
          })
        APUConfigSendUDPDataCount = APUConfigSendUDPDataCount + 1;
        console.log('发送数据: ' + "{\"ssid\":" + "\"" + _this.data.ssid + "\"" + "\"pwd\":" + "\"" + _this.data.password + "\"" + "}");

        if (APUConfigSendUDPDataCount>20)//发送了20次,还没绑定上
        {
          try { clearInterval(APUConfigSendUDPDataIntervalNumber); } catch (e) { }
          APUConfigSendUDPDataCount = 0;
          APUConfigconnectAPCount = 0;
          APUConfigStart = false;//
          udp.close();
          wx.hideLoading();
          wx.showModal({//弹出对话框
            title: '绑定失败',
            content: '请重新尝试'
          })
        }
      },
      1000,
      "null");//启动定时器



    //UDP接收到消息
    udp.onMessage(function (res) {
      console.log(res)
      let str = util.newAb2Str(res.message);//接收消息
      console.log('str===' + str)

      //{ "mac": "dc:4f:22:10:b0:ce", "ip": "192.168.0.101" }

      try { clearInterval(APUConfigSendUDPDataIntervalNumber); } catch (e) { }
      try { udp.close(); } catch (e) { }//关闭UDP
      APUConfigSendUDPDataCount = 0;
      APUConfigconnectAPCount = 0;
      APUConfigStart = false;//复位所有变量
      wx.hideLoading();//关闭提示框


      if (str!=null)
      {
        let json = JSON.parse(str);//解析JSON数据
        if (json != null)
        {
          let mac = json.mac;
          let ip = json.ip;
          if (mac != null)
          {
            wx.reLaunch({
              url:'../end/end'
            })
          }
        }
      }
    })

  },
    /**
  * 连接无线失败
  */
  connectWifiFail: function (res) 
  {
    var _this = this;
    
    if (APUConfigconnectAPCount<6)//尝试连接热点的次数
    {
      APUConfigconnectAPCount = APUConfigconnectAPCount + 1;
      console.log('连接Wi-Fi: Core-H7');
      wx.connectWifi//控制连接Wi-Fi无线信号
      ({
          SSID: "Core-H7",
        password: "11223344",
        success: _this.connectWifiSuccess,
        fail: _this.connectWifiFail
      })
    }
    else
    {
      APUConfigconnectAPCount = 0;
      APUConfigStart = false;//
      wx.hideLoading();
      wx.showModal({//弹出对话框
        title: '连接失败',
        content: '请重新尝试'
      })
    }
  },
  //点击绑定按钮
  BindClick: function () {
    var _this = this;

    if (_this.data.ssid.length == 0 || _this.data.password.length == 0) {
      wx.showModal({//弹出对话框
        title: '提示',
        content: 'Wi-Fi名称和密码不能为空'
      })
    } 
    else 
    {
      APUConfigStart = true;//开始配网
     
      //控制连接Wi-Fi无线信号
      wx.connectWifi
      ({
          SSID: "Core-H7",
        password: "11223344",
        success: _this.connectWifiSuccess,
        fail: _this.connectWifiFail
      })
      APUConfigconnectAPCount=0;
    }
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var _this = this;

    _this.GetWiFiSSID();//显示当前连接的Wi-Fi名称

    //启动网络状态监听
    wx.onNetworkStatusChange(function (res) 
    {
      console.log("绑定设备:网络改变" + res.isConnected + " " + res.networkType);
      if (res.networkType == "wifi")//当前连接的网络类型是WIFI
      {
        console.log("绑定设备:当前连接的网络类型是WIFI");
        if (!APUConfigStart)//没在配网状态
        {
          _this.GetWiFiSSID();
        }
      }
      else//其它网络
      {
        if (!APUConfigStart)//没在配网状态
        {
          _this.setData({//清空显示的wifi名称
            ssidValue: ""
          }) 
        }
      }
    })
  },
  /**
  * 获取链接的WIFI名称
  */
  GetWiFiSSID: function () {
    var _this = this;
    wx.startWifi({//启用WIFI功能
      success(res) {
        wx.getConnectedWifi//获取链接的Wi-Fi信息
          ({
            success(res) //获取到信息
            {
              if (!APUConfigStart)//没在配网状态
              {
                _this.data.ssid = res.wifi.SSID;
                _this.setData({
                  ssidValue: _this.data.ssid
                })
              }
              console.log("绑定设备:连接的Wi-Fi名称 " + _this.data.ssid);
            },
            fail(res) {
            }
          })
      }
    })
  },
  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    this.GetWiFiSSID();//显示当前连接的Wi-Fi名称
  },
  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    try { clearInterval(APUConfigSendUDPDataIntervalNumber); } catch (e) { }
    try { udp.close(); } catch (e) { }
    APUConfigSendUDPDataCount = 0;
    APUConfigconnectAPCount = 0;
    APUConfigStart = false;//
    wx.hideLoading();
  },
  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },
  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})