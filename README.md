# ofxTweeny

## Description
ofxTweeny is a wrapper of [Tweeny](https://github.com/mobius3/tweeny) for openFrameworks.


## Install
```shell
git clone --recursive https://github.com/RyoYumo/ofxTweeny.git
```

## How to use

### ofxTweeny::Tweener::update() in ofApp::update()
```cpp
void ofApp::update() {
    ofxTweeny::Tweener::update();
}
```

### Example

**Simple example**
```cpp
float value = 0.0;
void ofApp::keyPressed(int key) {
    float from = value;
    float to = ofRandomf();
    int duration = 1000; // ms
    ofxTweeny::Tweener::add(&value, from, to, duration);
}
```

**Customize animation curve**
```cpp
float value = 0.0;
void ofApp::keyPressed(int key) {
    float from = value;
    float to = ofRandomf();
    int duration = 1000; // ms
    ofxTweeny::Tweener::add(&value, from, to, duration, ofxTweeny::easeOutCirc);
}
```
[Ease functions](https://github.com/RyoYumo/ofxTweeny/blob/master/src/ofxTweeny.hpp#8)
