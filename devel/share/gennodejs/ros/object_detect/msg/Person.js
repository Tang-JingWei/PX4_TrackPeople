// Auto-generated. Do not edit!

// (in-package object_detect.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Person {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.detect_flag = null;
      this.cx = null;
      this.cy = null;
      this.dx = null;
      this.dy = null;
    }
    else {
      if (initObj.hasOwnProperty('detect_flag')) {
        this.detect_flag = initObj.detect_flag
      }
      else {
        this.detect_flag = 0;
      }
      if (initObj.hasOwnProperty('cx')) {
        this.cx = initObj.cx
      }
      else {
        this.cx = 0;
      }
      if (initObj.hasOwnProperty('cy')) {
        this.cy = initObj.cy
      }
      else {
        this.cy = 0;
      }
      if (initObj.hasOwnProperty('dx')) {
        this.dx = initObj.dx
      }
      else {
        this.dx = 0;
      }
      if (initObj.hasOwnProperty('dy')) {
        this.dy = initObj.dy
      }
      else {
        this.dy = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Person
    // Serialize message field [detect_flag]
    bufferOffset = _serializer.uint8(obj.detect_flag, buffer, bufferOffset);
    // Serialize message field [cx]
    bufferOffset = _serializer.uint8(obj.cx, buffer, bufferOffset);
    // Serialize message field [cy]
    bufferOffset = _serializer.uint8(obj.cy, buffer, bufferOffset);
    // Serialize message field [dx]
    bufferOffset = _serializer.uint8(obj.dx, buffer, bufferOffset);
    // Serialize message field [dy]
    bufferOffset = _serializer.uint8(obj.dy, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Person
    let len;
    let data = new Person(null);
    // Deserialize message field [detect_flag]
    data.detect_flag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [cx]
    data.cx = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [cy]
    data.cy = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dx]
    data.dx = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [dy]
    data.dy = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'object_detect/Person';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd4493f50035a5d649cf03c09f9d7953f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 detect_flag
    uint8 cx
    uint8 cy 
    uint8 dx	
    uint8 dy	
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Person(null);
    if (msg.detect_flag !== undefined) {
      resolved.detect_flag = msg.detect_flag;
    }
    else {
      resolved.detect_flag = 0
    }

    if (msg.cx !== undefined) {
      resolved.cx = msg.cx;
    }
    else {
      resolved.cx = 0
    }

    if (msg.cy !== undefined) {
      resolved.cy = msg.cy;
    }
    else {
      resolved.cy = 0
    }

    if (msg.dx !== undefined) {
      resolved.dx = msg.dx;
    }
    else {
      resolved.dx = 0
    }

    if (msg.dy !== undefined) {
      resolved.dy = msg.dy;
    }
    else {
      resolved.dy = 0
    }

    return resolved;
    }
};

module.exports = Person;
