//
//  Pic.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/18/21.
//

import UIKit
import DittoSyncKitSwift
import AVFoundation

struct Pic {
    let imageAttachment: DittoAttachment?
    let mimeType: String
}

enum AttachmentUnknownError: Error {
    case message(String)
}

extension Pic {
    static func insertPicture(image: UIImage) -> String? {
        guard let directory = try? FileManager.default.url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: false) as NSURL else { return nil }
        let fileName = "\(UUID().uuidString).jpg"
        guard let filePath = directory.appendingPathComponent(fileName) else {
            fatalError()
        }
        try? image.jpeg(.low)?.write(to: filePath)
        return filePath.path
    }
    
    static func getDataForAttachmentToken(_ token: DittoAttachmentToken, _ collection: String, _ callback: @escaping (_ progress: Float?, _ error: Error?, _ image: Data?, _ tempURL: URL?) -> Void) -> DittoAttachmentFetcher? {
        return Constants.ditto.store[collection].fetchAttachment(token: token) { (event) in
            switch event {
            case .completed(let attachment):
                do {

                    let data = try attachment.getData()
                    let tempURL = try TemporaryFile(creatingTempDirectoryForFilename: "\(UUID().uuidString).jpg").fileURL

                    try data.write(to: tempURL)
                    callback(1, nil, data, tempURL)
                } catch(let error) {
                    callback(nil, error, nil, nil)
                }

                break;
            case .deleted:
                break
            case .progress(let downloadedBytes, let totalBytes):
                callback(Float(downloadedBytes) / Float(totalBytes), nil, nil, nil)
                break
            @unknown default:
                callback(nil, AttachmentUnknownError.message("Unknown error"), nil, nil)
            }
        }
    }
}
