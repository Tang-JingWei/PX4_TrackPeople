// Auto-generated. Do not edit!

// (in-package fly.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class track {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.track_flag = null;
      this.track_cx = null;
      this.track_cy = null;
    }
    else {
      if (initObj.hasOwnProperty('track_flag')) {
        this.track_flag = initObj.track_flag
      }
      else {
        this.track_flag = 0;
      }
      if (initObj.hasOwnProperty('track_cx')) {
        this.track_cx = initObj.track_cx
      }
      else {
        this.track_cx = 0;
      }
      if (initObj.hasOwnProperty('track_cy')) {
        this.track_cy = initObj.track_cy
      }
      else {
        this.track_cy = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type track
    // Serialize message field [track_flag]
    bufferOffset = _serializer.uint8(obj.track_flag, buffer, bufferOffset);
    // Serialize message field [track_cx]
    bufferOffset = _serializer.uint8(obj.track_cx, buffer, bufferOffset);
    // Serialize message field [track_cy]
    bufferOffset = _serializer.uint8(obj.track_cy, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type track
    let len;
    let data = new track(null);
    // Deserialize message field [track_flag]
    data.track_flag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [track_cx]
    data.track_cx = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [track_cy]
    data.track_cy = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 3;
  }

  static datatype() {
    // Returns string type for a message object
    return 'fly/track';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '494b58be0cfd5a0309521cf7e47b2c2e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 track_flag
    uint8 track_cx
    uint8 track_cy
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new track(null);
    if (msg.track_flag !== undefined) {
      resolved.track_flag = msg.track_flag;
    }
    else {
      resolved.track_flag = 0
    }

    if (msg.track_cx !== undefined) {
      resolved.track_cx = msg.track_cx;
    }
    else {
      resolved.track_cx = 0
    }

    if (msg.track_cy !== undefined) {
      resolved.track_cy = msg.track_cy;
    }
    else {
      resolved.track_cy = 0
    }

    return resolved;
    }
};

module.exports = track;
