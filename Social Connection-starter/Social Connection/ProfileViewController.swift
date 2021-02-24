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
        i.clipsToBounds = true
        i.layer.masksToBounds = true
        return i
    }()
    
    lazy var nameLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .black
        label.font = UIFont.systemFont(ofSize: 20, weight: .semibold)
        return label
    }()
    
    lazy var countLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .lightGray
        label.font = UIFont.systemFont(ofSize: 12)
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

        pictureImageView.heightAnchor.constraint(equalToConstant: UIScreen.main.bounds.height * 0.45).isActive = true
        pictureImageView.leadingAnchor.constraint(equalTo: view.leadingAnchor).isActive = true
        pictureImageView.trailingAnchor.constraint(equalTo: view.trailingAnchor).isActive = true
        pictureImageView.topAnchor.constraint(equalTo: view.topAnchor).isActive = true
        
        backButton.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20).isActive = true
        backButton.topAnchor.constraint(equalTo: view.topAnchor, constant: 20).isActive = true
        backButton.heightAnchor.constraint(equalToConstant: 35).isActive = true
        backButton.widthAnchor.constraint(equalToConstant: 35).isActive = true

        nameLabel.topAnchor.constraint(equalTo: pictureImageView.bottomAnchor, constant: 15).isActive = true
        nameLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        
        countLabel.topAnchor.constraint(equalTo: nameLabel.bottomAnchor, constant: 2.5).isActive = true
        countLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        
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

    }
}
