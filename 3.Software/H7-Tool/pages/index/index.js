// index.js
// 获取应用实例
const app = getApp()

Page({


  StartButton:function(e){
    console.log('点击');
    wx.navigateTo({
      url: '../APUConfig/APUConfig',
     // url:'../end/end'
    })
  }

})


