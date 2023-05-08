
"use strict";

let GetIRExposure = require('./GetIRExposure.js')
let GetUVCExposure = require('./GetUVCExposure.js')
let SetIRGain = require('./SetIRGain.js')
let GetIRGain = require('./GetIRGain.js')
let SetUVCWhiteBalance = require('./SetUVCWhiteBalance.js')
let SetLDP = require('./SetLDP.js')
let GetUVCWhiteBalance = require('./GetUVCWhiteBalance.js')
let ResetIRExposure = require('./ResetIRExposure.js')
let SetIRExposure = require('./SetIRExposure.js')
let SetUVCExposure = require('./SetUVCExposure.js')
let SetIRFlood = require('./SetIRFlood.js')
let SetLaser = require('./SetLaser.js')
let GetDeviceType = require('./GetDeviceType.js')
let SetUVCGain = require('./SetUVCGain.js')
let GetUVCGain = require('./GetUVCGain.js')
let ResetIRGain = require('./ResetIRGain.js')
let SwitchIRCamera = require('./SwitchIRCamera.js')
let GetSerial = require('./GetSerial.js')
let GetCameraInfo = require('./GetCameraInfo.js')

module.exports = {
  GetIRExposure: GetIRExposure,
  GetUVCExposure: GetUVCExposure,
  SetIRGain: SetIRGain,
  GetIRGain: GetIRGain,
  SetUVCWhiteBalance: SetUVCWhiteBalance,
  SetLDP: SetLDP,
  GetUVCWhiteBalance: GetUVCWhiteBalance,
  ResetIRExposure: ResetIRExposure,
  SetIRExposure: SetIRExposure,
  SetUVCExposure: SetUVCExposure,
  SetIRFlood: SetIRFlood,
  SetLaser: SetLaser,
  GetDeviceType: GetDeviceType,
  SetUVCGain: SetUVCGain,
  GetUVCGain: GetUVCGain,
  ResetIRGain: ResetIRGain,
  SwitchIRCamera: SwitchIRCamera,
  GetSerial: GetSerial,
  GetCameraInfo: GetCameraInfo,
};
