//
//  Default.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/14/21.
//

import Foundation

struct Defaults {
    
    static let userIdKey = "userIdKey"
    static let userInfoKey = "userInfoKey"
    static let (imagePath, name, linkedin, instagram, twitter, facebook) = ("imagePath", "name", "linkedin", "instagram", "twitter", "facebook")

    struct UserModel : Codable {
        var imagePath : String?
        var name : String?
        var linkedin : String?
        var instagram : String?
        var twitter : String?
        var facebook : String?
    }

    static func saveUser(imagePath: String, name: String, linkedin: String, instagram: String, twitter: String, facebook: String)
    {
        let user = UserModel(imagePath: imagePath, name: name, linkedin: linkedin, instagram: instagram, twitter: twitter, facebook: facebook)
        if let encoded = try? JSONEncoder().encode(user) {
            UserDefaults.standard.set(encoded, forKey: userInfoKey)
        }
    }
        
    static func getUser() -> UserModel?
    {
        if let userData = UserDefaults.standard.data(forKey: userInfoKey),
            let user = try? JSONDecoder().decode(UserModel.self, from: userData) {
            return user
        }
        
        return nil
    }
    
    static func getUserId() -> String
    {
        return UserDefaults.standard.string(forKey: userIdKey) ?? ""
    }
    
    static func setUserId(_ userId : String) {
        UserDefaults.standard.set(userId, forKey: userIdKey)
    }
    
    static func getSocialCount() -> Int {
        var count = 0
        if let user = Defaults.getUser() {
            if let fb = user.facebook {
                if !fb.isEmpty {
                    count += 1
                }
            }
            if let linkedin = user.linkedin {
                if !linkedin.isEmpty {
                    count += 1
                }
            }
            if let instagram = user.instagram {
                if !instagram.isEmpty {
                    count += 1
                }
            }
            if let twitter = user.twitter {
                if !twitter.isEmpty {
                    count += 1
                }
            }
        }
        
        return count
    }
}
