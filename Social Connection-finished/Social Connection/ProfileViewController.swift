//
//  ProfileViewController.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/18/21.
//

import Foundation
import UIKit
import DittoSyncKitSwift

class ProfileViewController: UIViewController {
    
    var thumbnailFetcher: DittoAttachmentFetcher?
    var profile: DittoDocument?
    
    let linkedinColor = UIColor(red: 0.05, green: 0.46, blue: 0.66, alpha: 1.00)
    let facebookColor = UIColor(red: 0.23, green: 0.35, blue: 0.60, alpha: 1.00)
    let instagramColor = UIColor(red: 0.54, green: 0.23, blue: 0.73, alpha: 1.00)
    let twitterColor = UIColor(red: 0.11, green: 0.63, blue: 0.95, alpha: 1.00)
    
    let facebookUrl = "https://www.facebook.com/%@/"
    let linkedinUrl = "https://www.linkedin.com/in/%@/"
    let instagramUrl = "https://www.instagram.com/%@/"
    let twitterUrl = "https://twitter.com/%@/"
    
    var instagramName: String?
    var facebookName: String?
    var linkedinName: String?
    var twitterName: String?
    
    lazy var backButton: UIButton = {
        let button = UIButton()
        button.translatesAutoresizingMaskIntoConstraints = false
        button.setImage(UIImage.init(named: "down"), for: .normal)
        button.addTarget(self, action: #selector(goBack), for: .touchUpInside)
        return button
    }()

    lazy var pictureImageView: UIImageView = {
        let i = UIImageView()
        i.translatesAutoresizingMaskIntoConstraints = false
        i.contentMode = .scaleAspectFill
        i.layer.cornerRadius = 75
        i.clipsToBounds = true
        i.layer.masksToBounds = true
        return i
    }()
    
    lazy var nameLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .black
        label.font = UIFont.systemFont(ofSize: 20, weight: .semibold)
        label.textAlignment = .center
        return label
    }()
    
    lazy var countLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .lightGray
        label.font = UIFont.systemFont(ofSize: 12)
        label.textAlignment = .center
        return label
    }()
    
    lazy var stackView: UIStackView = {
        let view = UIStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.axis = .vertical
        view.distribution = .equalSpacing
        view.spacing = 5
        return view
    }()
    
    override func loadView() {
        super.loadView()
        
        view.addSubview(pictureImageView)
        view.addSubview(backButton)
        view.addSubview(nameLabel)
        view.addSubview(countLabel)
        view.addSubview(stackView)

        pictureImageView.heightAnchor.constraint(equalToConstant: 150).isActive = true
        pictureImageView.widthAnchor.constraint(equalToConstant: 150).isActive = true
        pictureImageView.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
        pictureImageView.topAnchor.constraint(equalTo: view.topAnchor, constant: UIScreen.main.bounds.height * 0.15).isActive = true
        
        backButton.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20).isActive = true
        backButton.topAnchor.constraint(equalTo: view.topAnchor, constant: 20).isActive = true
        backButton.heightAnchor.constraint(equalToConstant: 35).isActive = true
        backButton.widthAnchor.constraint(equalToConstant: 35).isActive = true

        nameLabel.topAnchor.constraint(equalTo: pictureImageView.bottomAnchor, constant: 15).isActive = true
        nameLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        nameLabel.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20).isActive = true

        countLabel.topAnchor.constraint(equalTo: nameLabel.bottomAnchor, constant: 2.5).isActive = true
        countLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        countLabel.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20).isActive = true

        stackView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        stackView.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20).isActive = true
        stackView.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -10).isActive = true
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        configureWithData()
    }
    
    @objc func goBack() {
        dismiss(animated: true, completion: nil)
    }
    
    @objc func goToLinkedin() {
        openSite(String(format: linkedinUrl, linkedinName!))
    }
    
    @objc func goToInstagram() {
        openSite(String(format: instagramUrl, instagramName!))
    }
    
    @objc func goToTwitter() {
        openSite(String(format: twitterUrl, twitterName!))
    }
    
    @objc func goToFacebook() {
        openSite(String(format: facebookUrl, facebookName!))
    }
    
    func openSite(_ url: String) {
        guard let url = URL(string: url) else {
            return
        }
        if UIApplication.shared.canOpenURL(url) {
            UIApplication.shared.open(url, options: [:], completionHandler: nil)
        }
    }
    
    func configureWithData() {
        guard let profile = self.profile else { return }
        nameLabel.text = profile["name"].stringValue
        var count = 0
        let instagram = profile["instagram"].stringValue
        let linkedin = profile["linkedin"].stringValue
        let facebook = profile["facebook"].stringValue
        let twitter = profile["twitter"].stringValue
        
        if !instagram.isEmpty {
            count += 1
            instagramName = instagram
            let instagramView = SocialView()
            instagramView.backgroundColor = instagramColor
            instagramView.nameLabel.text = "Instagram"
            instagramView.iconImageView.image = UIImage.init(named: "instagram")
            instagramView.button.addTarget(self, action: #selector(goToInstagram), for: .touchUpInside)
            stackView.addArrangedSubview(instagramView)
        }
        
        if !linkedin.isEmpty {
            count += 1
            linkedinName = linkedin
            let linkedinView = SocialView()
            linkedinView.backgroundColor = linkedinColor
            linkedinView.nameLabel.text = "Linkedin"
            linkedinView.iconImageView.image = UIImage.init(named: "linkedin")
            linkedinView.button.addTarget(self, action: #selector(goToLinkedin), for: .touchUpInside)
            stackView.addArrangedSubview(linkedinView)
        }
        
        if !facebook.isEmpty {
            count += 1
            facebookName = facebook
            let facebookView = SocialView()
            facebookView.backgroundColor = facebookColor
            facebookView.nameLabel.text = "Facebook"
            facebookView.iconImageView.image = UIImage.init(named: "facebook")
            facebookView.button.addTarget(self, action: #selector(goToFacebook), for: .touchUpInside)
            stackView.addArrangedSubview(facebookView)
        }
        
        if !twitter.isEmpty {
            count += 1
            twitterName = twitter
            let twitterView = SocialView()
            twitterView.backgroundColor = twitterColor
            twitterView.nameLabel.text = "Twitter"
            twitterView.iconImageView.image = UIImage.init(named: "twitter")
            twitterView.button.addTarget(self, action: #selector(goToTwitter), for: .touchUpInside)
            stackView.addArrangedSubview(twitterView)
        }

        let accountsLabel = count == 1 ? "Account" : "Accounts"
        countLabel.text = "\(count) Social \(accountsLabel)"
        
        let imageAttachmentToken = profile["attachment"].attachmentToken
        guard let attachmentToken = imageAttachmentToken else {
            self.pictureImageView.image = nil
            return
        }
        thumbnailFetcher = Pic.getDataForAttachmentToken(attachmentToken, "connections", { (progress, error, data, _) in
            DispatchQueue.main.async {
                if let data = data {
                    UIView.transition(with: self.pictureImageView,
                                      duration: 0.3,
                                      options: .transitionCrossDissolve,
                                      animations: {
                                        self.pictureImageView.image = UIImage(data: data)
                                      },
                                      completion: nil)
                }

            }
        })
    }
}
