#ifndef OFX_TWEENY_HPP_
#define OFX_TWEENY_HPP_

#include "../libs/tweeny/include/tweeny.h"
#include <vector>

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

template<typename T>
using Tween = tweeny::tween<T>;

class Tweener {
public:
    template<typename T>
    static void add(T* ptr, const Tween<T>& tween)
    {
        remove(ptr);
        auto item = std::make_shared<TweenItemWrapper<T>>(ptr, tween);
        instance().items_.push_back(item);
    }
    
    template<typename T, typename EaseFunc=tweeny::easing::linearEasing>
    static void add(T* ptr,
                    const T& from,
                    const T& to,
                    std::uint16_t duration,
                    EaseFunc f=linear)
    {
        add(ptr, Tween<T>::from(from).to(to).during(duration).via(f));
    }
    
    
    template<typename T, typename EaseFunc=tweeny::easing::linearEasing>
    static void add(T* ptr, const std::vector<T>& to, std::uint16_t duration, EaseFunc f=linear){
        auto tween = Tween<T>::from(*ptr);
        for(auto i = 0; i < to.size(); ++i){
            tween.to(to[i]).during(duration).via(f);
        }
        add(ptr, tween);
    }
    
    
    template<typename T>
    static void remove(T* ptr){
        auto& items = instance().items_;
        auto iter = std::find_if(items.begin(), items.end(), [ptr](const std::shared_ptr<BaseTweenItem>& item){
            return item->ptr() == ptr;
        });
        if(iter!=items.end()){
            items.erase(iter);
        }
    }
    
    static void update(){
        auto& items = instance().items_;
        auto result = std::remove_if(items.begin(), items.end(), [](const std::shared_ptr<BaseTweenItem>& item){
            return item->complete();
        });
        items.erase(result, items.end());
        std::for_each(items.begin(), items.end(), [](std::shared_ptr<BaseTweenItem>& item){
            item->update(instance().tick_);
        });
    }

    static void set_fps(int fps) {
        instance().tick_ = 1000 / fps;
    }
    
private:
    
    class BaseTweenItem {
    public:
        virtual ~BaseTweenItem() = default;
        virtual void update(std::uint16_t tick) = 0;
        virtual bool complete() const = 0;
        virtual void* ptr() const = 0;
    };
    
    template<typename T>
    class TweenItemWrapper : public BaseTweenItem {
    public:
        TweenItemWrapper(T* ptr, const Tween<T>& tween)
        : ptr_{ptr}, tween_{tween}{
        }
        
        void update(std::uint16_t tick) override {
            *ptr_ = tween_.step(tick);
        }
        
        bool complete() const override {
            return tween_.progress() >= 1.0 ? true : false;
        }
        
        void* ptr() const override {
            return ptr_;
        }
        
    private:
        Tween<T> tween_;
        T* ptr_;
        
    };
    
    std::uint16_t tick_ { 16 };
    Tweener(){}
    static Tweener& instance(){
        static Tweener instance{};
        return instance;
    }
    std::vector<std::shared_ptr<BaseTweenItem>> items_;
};

} // namespace ofxTweeny




#endif // OFX_TWEENEY
