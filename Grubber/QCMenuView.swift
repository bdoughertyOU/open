//
//  QCMethod.swift
//
//  Version 1.02
//
//  www.quartzcodeapp.com
//

#if os(iOS)
    import UIKit
    #else
    import Cocoa
#endif

class QCMethod
{
    class func reverseAnimation(anim : CAAnimation, totalDuration : CGFloat) -> CAAnimation{
        var duration : CGFloat = CGFloat(anim.duration + (anim.autoreverses ? anim.duration : 0))
        if anim.repeatCount > 1 {
            duration = duration * CGFloat(anim.repeatCount)
        }
        let endTime = CGFloat(anim.beginTime) + duration
        let reverseStartTime = totalDuration - endTime
        
        var newAnim : CAAnimation!
        
        //Reverse timing function closure
        let reverseTimingFunction =
        {
            (theAnim:CAAnimation) -> Void  in
            let timingFunction = theAnim.timingFunction;
            if timingFunction != nil{
                var first : [Float] = [0,0]
                var second : [Float] = [0,0]
                timingFunction.getControlPointAtIndex(1, values: &first)
                timingFunction.getControlPointAtIndex(2, values: &second)
                
                theAnim.timingFunction = CAMediaTimingFunction(controlPoints: 1-second[0], 1-second[1], 1-first[0], 1-first[1])
            }
        }
        
        //Reverse animation values appropriately
        if let basicAnim = anim as? CABasicAnimation{
            if !anim.autoreverses{
                let fromValue: AnyObject! = basicAnim.toValue
                basicAnim.toValue = basicAnim.fromValue
                basicAnim.fromValue = fromValue
                reverseTimingFunction(basicAnim)
            }
            basicAnim.beginTime = CFTimeInterval(reverseStartTime)
            
            
            if reverseStartTime > 0 {
                let groupAnim = CAAnimationGroup()
                groupAnim.animations = [basicAnim]
                groupAnim.duration = maxDurationFromAnimations(groupAnim.animations as! [CAAnimation])
                groupAnim.animations?.map{$0.setValue(kCAFillModeBoth, forKey: "fillMode")}
                newAnim = groupAnim
            }
            else{
                newAnim = basicAnim
            }
            
        }
        else if let keyAnim = anim as? CAKeyframeAnimation{
            if !anim.autoreverses{
                let values = keyAnim.values?.reverse()
                keyAnim.values = values;
                reverseTimingFunction(keyAnim)
            }
            keyAnim.beginTime = CFTimeInterval(reverseStartTime)
            
            if reverseStartTime > 0 {
                let groupAnim = CAAnimationGroup()
                groupAnim.animations = [keyAnim]
                groupAnim.duration = maxDurationFromAnimations(groupAnim.animations as! [CAAnimation])
                groupAnim.animations?.map{$0.setValue(kCAFillModeBoth, forKey: "fillMode")}
                newAnim = groupAnim
            }else{
                newAnim = keyAnim
            }
        }
        else if let groupAnim = anim as? CAAnimationGroup{
            var newSubAnims : [CAAnimation] = []
            for subAnim in groupAnim.animations as! [CAAnimation] {
                let newSubAnim = reverseAnimation(subAnim, totalDuration: totalDuration)
                newSubAnims.append(newSubAnim)
            }
            
            groupAnim.animations = newSubAnims
            groupAnim.animations?.map{$0.setValue(kCAFillModeBoth, forKey: "fillMod")}
            groupAnim.duration = maxDurationFromAnimations(newSubAnims)
            newAnim = groupAnim
        }else{
            newAnim = anim
        }
        return newAnim
    }
    
    class func maxDurationFromAnimations(anims : [CAAnimation]) -> CFTimeInterval{
        var maxDuration: CGFloat = 0;
        for anim in anims {
            maxDuration = max(CGFloat(anim.beginTime + anim.duration) * CGFloat(anim.repeatCount == 0 ? 1.0 : anim.repeatCount) * (anim.autoreverses ? 2.0 : 1.0), maxDuration);
        }
        
        if isinf(maxDuration){ return NSTimeInterval(NSIntegerMax)}
        
        return CFTimeInterval(maxDuration);
    }
    
    class func maxDurationOfEffectAnimation(anim : CAAnimation, sublayersCount : NSInteger) -> CFTimeInterval{
        var maxDuration : CGFloat = 0
        if let groupAnim = anim as? CAAnimationGroup{
            for subAnim in groupAnim.animations as! [CAAnimation]{
                
                var delay : CGFloat = 0
                let instDelay = subAnim.valueForKey("instanceDelay")?.floatValue;
                if (instDelay != nil) {
                    delay = CGFloat(instDelay!) * CGFloat(sublayersCount - 1);
                }
                var repeatCountDuration : CGFloat = 0;
                if subAnim.repeatCount > 1 {
                    repeatCountDuration = CGFloat(subAnim.duration) * CGFloat(subAnim.repeatCount-1);
                }
                var duration : CGFloat = 0;
                
                duration = CGFloat(subAnim.beginTime) + (subAnim.autoreverses ? CGFloat(subAnim.duration) : CGFloat(0)) + delay + CGFloat(subAnim.duration) + CGFloat(repeatCountDuration);
                maxDuration = max(duration, maxDuration);
            }
        }
        return CFTimeInterval(maxDuration);
    }
    
    class func updateValueFromAnimationsForLayers(layers : [CALayer]){
        CATransaction.begin()
        CATransaction.setDisableActions(true)
        
        for aLayer in layers{
            if let keys = aLayer.animationKeys() as! [String]!{
                for animKey in keys{
                    let anim = aLayer.animationForKey(animKey)
                    updateValueForAnim(anim, theLayer: aLayer);
                }
            }
            
        }
        
        CATransaction.commit()
    }
    
    class func updateValueForAnim(anim : CAAnimation, theLayer : CALayer){
        if let basicAnim = anim as? CABasicAnimation{
            if (!basicAnim.autoreverses) {
                theLayer.setValue(basicAnim.toValue, forKey: basicAnim.keyPath)
            }
        }else if let keyAnim = anim as? CAKeyframeAnimation{
            if (!keyAnim.autoreverses) {
                theLayer.setValue(keyAnim.values?.last, forKey: keyAnim.keyPath)
            }
        }else if let groupAnim = anim as? CAAnimationGroup{
            for subAnim in groupAnim.animations as! [CAAnimation]{
                updateValueForAnim(subAnim, theLayer: theLayer)
            }
        }
    }
    
    class func addSublayersAnimation(anim : CAAnimation, key : String, layer : CALayer){
        return addSublayersAnimation(anim, key: key, layer: layer, reverseAnimation: false, totalDuration: 0)
    }
    
    class func addSublayersAnimation(anim : CAAnimation, key : String, layer : CALayer, reverseAnimation : Bool, totalDuration : CGFloat){
        let sublayers = layer.sublayers
        let sublayersCount = sublayers.count
        
        var setBeginTime =
        {
            (subAnim:CAAnimation, sublayerIdx:NSInteger) -> Void  in
            
            var delay : CGFloat = 0
            let instDelay = subAnim.valueForKey("instanceDelay")?.floatValue;
            if (instDelay != nil) {
                let instanceDelay = CGFloat(instDelay!)
                let orderType : NSInteger = (subAnim.valueForKey("instanceOrder")!).integerValue
                switch (orderType) {
                case 0: subAnim.beginTime = CFTimeInterval(CGFloat(subAnim.beginTime) + CGFloat(sublayerIdx) * instanceDelay)
                case 1: subAnim.beginTime = CFTimeInterval(CGFloat(subAnim.beginTime) + CGFloat(sublayersCount - sublayerIdx - 1) * instanceDelay)
                case 2:
                    let middleIdx     = sublayersCount/2
                    let begin         = CGFloat(abs(middleIdx - sublayerIdx)) * instanceDelay
                    subAnim.beginTime += CFTimeInterval(begin)
                    
                case 3:
                    let middleIdx     = sublayersCount/2
                    let begin         = CGFloat(middleIdx - abs((middleIdx - sublayerIdx))) * instanceDelay
                    subAnim.beginTime     += CFTimeInterval(begin)
                    
                default:
                    break
                }
            }
        }
        
        for (idx, sublayer) in enumerate(sublayers) {
            
            if let groupAnim = anim.copy() as? CAAnimationGroup{
                var newSubAnimations : [CAAnimation] = []
                for subAnim in groupAnim.animations{
                    newSubAnimations.append(subAnim.copy() as! CAAnimation)
                }
                groupAnim.animations = newSubAnimations
                let animations = groupAnim.animations
                for sub in animations as! [CAAnimation]{
                    setBeginTime(sub, idx)
                    //Reverse animation if needed
                    if reverseAnimation {
                        self.reverseAnimation(sub, totalDuration: totalDuration)
                    }
                    
                }
                sublayer.addAnimation(groupAnim, forKey: key)
            }
            else{
                let copiedAnim = anim.copy() as! CAAnimation
                setBeginTime(copiedAnim, idx)
                sublayer.addAnimation(copiedAnim, forKey: key)
            }
            
        }
    }
    
    class func gradientLayerOf(layer : CALayer) -> CAGradientLayer!{
        for sublayer in layer.sublayers! {
            if let gradientLayer = sublayer as? CAGradientLayer{
                return gradientLayer
            }
        }
        return nil
    }
    
    
    #if os(iOS)
    class func alignToBottomPath(path : UIBezierPath, layer: CALayer) -> UIBezierPath{
    let diff = CGRectGetMaxY(layer.bounds) - CGRectGetMaxY(path.bounds)
    let transform = CGAffineTransformTranslate(CGAffineTransformIdentity, 0, diff)
    path.applyTransform(transform)
    return path;
    }
    
    class func offsetPath(path : UIBezierPath, offset : CGPoint) -> UIBezierPath{
    let affineTransform = CGAffineTransformTranslate(CGAffineTransformIdentity, offset.x, offset.y)
    path.applyTransform(affineTransform)
    return path
    }
    
    
    #else
    class func offsetPath(path : NSBezierPath, offset : CGPoint) -> NSBezierPath{
        let xfm = NSAffineTransform()
        xfm.translateXBy(offset.x, yBy:offset.y)
        path.transformUsingAffineTransform(xfm)
        return path
    }
    
    
    #endif
}


#if os(iOS)
    #else
    extension NSBezierPath {
        
        var quartzPath: CGPathRef {
            
            get {
                return self.transformToCGPath()
            }
        }
        
        /// Transforms the NSBezierPath into a CGPathRef
        ///
        /// :returns: The transformed NSBezierPath
        private func transformToCGPath() -> CGPathRef {
            
            // Create path
            var path = CGPathCreateMutable()
            var points = UnsafeMutablePointer<NSPoint>.alloc(3)
            let numElements = self.elementCount
            
            if numElements > 0 {
                
                var didClosePath = true
                
                for index in 0..<numElements {
                    
                    let pathType = self.elementAtIndex(index, associatedPoints: points)
                    
                    switch pathType {
                        
                    case .MoveToBezierPathElement:
                        CGPathMoveToPoint(path, nil, points[0].x, points[0].y)
                    case .LineToBezierPathElement:
                        CGPathAddLineToPoint(path, nil, points[0].x, points[0].y)
                        didClosePath = false
                    case .CurveToBezierPathElement:
                        CGPathAddCurveToPoint(path, nil, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y)
                        didClosePath = false
                    case .ClosePathBezierPathElement:
                        CGPathCloseSubpath(path)
                        didClosePath = true
                    }
                }
                
                //if !didClosePath { CGPathCloseSubpath(path) }
            }
            
            points.dealloc(3)
            return path
        }
    }
    
    
    extension NSImage{
        
        func cgImage() -> CGImageRef{
            let data = self.TIFFRepresentation
            var imageRef : CGImageRef!
            var sourceRef : CGImageSourceRef!
            
            sourceRef = CGImageSourceCreateWithData(data, nil)
            if (sourceRef != nil) {
                imageRef = CGImageSourceCreateImageAtIndex(sourceRef, 0, nil)
            }
            return imageRef
        }
    }
    
    
#endif
