//
//  Extensions.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/18/21.
//

import Foundation
import UIKit
import Photos
import AVFoundation


extension UIImage {
    enum JPEGQuality: CGFloat {
            case lowest  = 0
            case low     = 0.25
            case medium  = 0.5
            case high    = 0.75
            case highest = 1
        }

        /// Returns the data for the specified image in JPEG format.
        /// If the image object’s underlying image data has been purged, calling this function forces that data to be reloaded into memory.
        /// - returns: A data object containing the JPEG data, or nil if there was a problem generating the data. This function may return nil if the image has no data or if the underlying CGImageRef contains data in an unsupported bitmap format.
        func jpeg(_ jpegQuality: JPEGQuality) -> Data? {
            return jpegData(compressionQuality: jpegQuality.rawValue)
        }
}


extension PHAsset {
    var thumbnailImage : UIImage {
        get {
            let manager = PHImageManager.default()
            let option = PHImageRequestOptions()
            var thumbnail = UIImage()
            option.isSynchronous = true
            manager.requestImage(for: self, targetSize: CGSize(width: 300, height: 300), contentMode: .aspectFit, options: option, resultHandler: {(result, info)->Void in
                thumbnail = result!
            })
            return thumbnail
        }
    }
}
