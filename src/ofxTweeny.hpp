#ifndef OFX_TWEENY_HPP_
#define OFX_TWEENY_HPP_

#include "../libs/tweeny/include/tweeny.h"
#include <vector>
#include "glm/glm.hpp"
#include "ofEvents.h"

namespace ofxTweeny{
static constexpr auto linear = tweeny::easing::linear;
static constexpr auto easeInQuad  = tweeny::easing::quadraticIn;
static constexpr auto easeOutQuad = tweeny::easing::quadraticOut;
static constexpr auto easeInOutQuad = tweeny::easing::quadraticInOut;
static constexpr auto easeInCubic = tweeny::easing::cubicIn;
static constexpr auto easeOutCubic = tweeny::easing::cubicOut;
static constexpr auto easeInOutCubic = tweeny::easing::cubicInOut;
static constexpr auto easeInQuart = tweeny::easing::quarticIn;
static constexpr auto easeOutQuart = tweeny::easing::quarticOut;
static constexpr auto easeInOutQuart = tweeny::easing::quarticInOut;
static constexpr auto easeInQuint = tweeny::easing::quinticIn;
static constexpr auto easeOutQuint = tweeny::easing::quinticOut;
static constexpr auto easeInOutQuint = tweeny::easing::quinticInOut;
static constexpr auto easeInSinusoidal = tweeny::easing::sinusoidalIn;
static constexpr auto easeOutSinusoidal = tweeny::easing::sinusoidalOut;
static constexpr auto easeInOutSinusoidal = tweeny::easing::sinusoidalInOut;
static constexpr auto easeInExpo = tweeny::easing::exponentialIn;
static constexpr auto easeOutExpo = tweeny::easing::exponentialOut;
static constexpr auto easeInOutExpo = tweeny::easing::exponentialInOut;
static constexpr auto easeInCirc = tweeny::easing::circularIn;
static constexpr auto easeOutCirc = tweeny::easing::circularOut;
static constexpr auto easeInOutCirc = tweeny::easing::circularInOut;
static constexpr auto easeInBounce = tweeny::easing::bounceIn;
static constexpr auto easeOutBounce = tweeny::easing::bounceOut;
static constexpr auto easeInOutBounce = tweeny::easing::bounceInOut;
static constexpr auto easeInElastic  = tweeny::easing::elasticIn;
static constexpr auto easeOutElastic  = tweeny::easing::elasticOut;
static constexpr auto easeInOutElastic  = tweeny::easing::elasticInOut;

namespace detail{
class TweenItem {
public:
    using TweenType = tweeny::tween<float>;
    
    template<typename EaseFunc>
    TweenItem(float* ptr,
              float from,
              float to,
              float duration, EaseFunc f)
    : ptr_{ptr}{
        *ptr_ = from;
        tween_ = TweenType::from(from).to(to).during(duration).via(f);
    }
    
    void update(int step){
        *ptr_ = tween_.step(step);
    }

    bool complete() const {
        return tween_.progress() >= 1.0 ? true : false;
    }
    const float* ptr() const { return ptr_; }
    
private:
    float* ptr_;
    TweenType tween_;

};
}

class Tweener {
public:
    template<typename EaseFunc=tweeny::easing::linearEasing>
    static void add(float* ptr,
                    float from,
                    float to,
                    float duration,
                    EaseFunc f=linear)
    {
        remove(ptr);
        instance().items_.push_back(detail::TweenItem(ptr, from, to, duration, f));
    }
    
    
    template<typename EaseFunc=tweeny::easing::linearEasing>
       static void add(glm::vec2* ptr,
                       const glm::vec2& from,
                       const glm::vec2& to,
                       float duration,
                       EaseFunc f=linear)
       {
           add(&ptr->x, from.x, to.x, duration, f);
           add(&ptr->y, from.y, to.y, duration, f);
       }
    
    template<typename EaseFunc=tweeny::easing::linearEasing>
    static void add(glm::vec3* ptr,
                    const glm::vec3& from,
                    const glm::vec3& to,
                    float duration,
                    EaseFunc f=linear)
    {
        add(&ptr->x, from.x, to.x, duration, f);
        add(&ptr->y, from.y, to.y, duration, f);
        add(&ptr->z, from.z, to.z, duration, f);
    }
    
    static void remove(float* ptr){
        auto& items = instance().items_;
        auto iter = std::find_if(items.begin(), items.end(), [ptr](const detail::TweenItem& item){
            return item.ptr() == ptr;
        });
        if(iter!=items.end()){
            items.erase(iter);
        }
    }
    
    static void update(){
        auto& items = instance().items_;
        auto result = std::remove_if(items.begin(), items.end(), [](const detail::TweenItem& item){
            return item.complete();
        });
        items.erase(result, items.end());
        std::for_each(items.begin(), items.end(), [](detail::TweenItem& item){
            item.update(kTick);
        });
    }
    
private:
    static constexpr auto kTick = 16;
    Tweener(){}
    static Tweener& instance(){
        static Tweener instance{};
        return instance;
    }
    std::vector<detail::TweenItem> items_;
};

} // namespace ofxTweeny




#endif // OFX_TWEENEY
