//
//  AttendeeTableViewCell.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/16/21.
//

import Foundation
import UIKit
import DittoSyncKitSwift
import CoreMotion

class AttendeeTableViewCell: UITableViewCell {
    static let REUSE_ID = "AttendeeTableViewCell"
    var thumbnailFetcher: DittoAttachmentFetcher?
    private weak var shadowView: UIView?
    private let motionManager = CMMotionManager()
    
    let viewContainer : UIView = {
        let view = UIView()
        view.backgroundColor = UIColor.white
        view.layer.cornerRadius = 10
        view.layer.masksToBounds = true
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()

    lazy var borderView: UIView = {
        let view = UIView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.layer.borderColor = UIColor.systemBlue.cgColor
        view.layer.borderWidth = 0.5
        view.layer.cornerRadius = 35
        view.layer.masksToBounds = true
        return view
    }()

    lazy var pictureImageView: UIImageView = {
        let i = UIImageView()
        i.translatesAutoresizingMaskIntoConstraints = false
        i.contentMode = .scaleAspectFill
        i.layer.masksToBounds = true
        i.layer.cornerRadius = 32.5
        i.backgroundColor = UIColor.systemGray
        return i
    }()
    
    lazy var inviteButton: UIButton = {
        let button = UIButton()
        button.translatesAutoresizingMaskIntoConstraints = false
        button.backgroundColor = .systemGroupedBackground
        button.layer.cornerRadius = 15
        button.setTitle("Add", for: .normal)
        button.setTitleColor(.systemBlue, for: .normal)
        button.layer.masksToBounds = true
        return button
    }()
    
    lazy var nameLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .black
        label.font = UIFont.systemFont(ofSize: 16)
        return label
    }()
    
    lazy var countLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .lightGray
        label.font = UIFont.systemFont(ofSize: 12)
        return label
    }()

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        selectionStyle = .none
        self.backgroundColor = .clear
        
        contentView.addSubview(viewContainer)
        viewContainer.topAnchor.constraint(equalTo: contentView.topAnchor, constant: -10).isActive = true
        viewContainer.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 15).isActive = true
        viewContainer.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -15).isActive = true
        viewContainer.bottomAnchor.constraint(equalTo: contentView.bottomAnchor, constant: -10).isActive = true

        
        viewContainer.addSubview(inviteButton)
        viewContainer.addSubview(borderView)
        borderView.addSubview(pictureImageView)
        viewContainer.addSubview(nameLabel)
        viewContainer.addSubview(countLabel)

        inviteButton.trailingAnchor.constraint(equalTo: viewContainer.trailingAnchor, constant: -15).isActive = true
        inviteButton.heightAnchor.constraint(equalToConstant: 30).isActive = true
        inviteButton.widthAnchor.constraint(equalToConstant: 75).isActive = true
        inviteButton.topAnchor.constraint(equalTo: viewContainer.topAnchor, constant: 40).isActive = true
        inviteButton.bottomAnchor.constraint(equalTo: viewContainer.bottomAnchor, constant: -40).isActive = true
        
        borderView.heightAnchor.constraint(equalToConstant: 70).isActive = true
        borderView.widthAnchor.constraint(equalToConstant: 70).isActive = true
        borderView.centerYAnchor.constraint(equalTo: viewContainer.centerYAnchor).isActive = true
        borderView.leadingAnchor.constraint(equalTo: viewContainer.leadingAnchor, constant: 20).isActive = true

        pictureImageView.heightAnchor.constraint(equalToConstant: 65).isActive = true
        pictureImageView.widthAnchor.constraint(equalToConstant: 65).isActive = true
        pictureImageView.centerYAnchor.constraint(equalTo: borderView.centerYAnchor).isActive = true
        pictureImageView.centerXAnchor.constraint(equalTo: borderView.centerXAnchor).isActive = true
        
        nameLabel.leadingAnchor.constraint(equalTo: borderView.trailingAnchor, constant: 10).isActive = true
        nameLabel.bottomAnchor.constraint(equalTo: borderView.centerYAnchor, constant: 1).isActive = true
        
        countLabel.leadingAnchor.constraint(equalTo: borderView.trailingAnchor, constant: 10).isActive = true
        countLabel.topAnchor.constraint(equalTo: borderView.centerYAnchor, constant: 1).isActive = true
    }
    
    override func prepareForReuse() {
        pictureImageView.image = nil
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        let margins = UIEdgeInsets(top: 10, left: 0, bottom: 0, right: 0)
        contentView.frame = contentView.frame.inset(by: margins)
        configureShadow()
    }
    
    private func configureShadow() {
        // Shadow View
        self.shadowView?.removeFromSuperview()
        let shadowView = UIView(frame: CGRect(x: 20,
                                              y: 20,
                                              width: bounds.width - (2 * 20),
                                              height: bounds.height - (2 * 20)))
        insertSubview(shadowView, at: 0)
        self.shadowView = shadowView
        
        // Roll/Pitch Dynamic Shadow
        if motionManager.isDeviceMotionAvailable {
            motionManager.deviceMotionUpdateInterval = 0.02
            motionManager.startDeviceMotionUpdates(to: .main, withHandler: { (motion, error) in
                if let motion = motion {
                    let pitch = motion.attitude.pitch * 10
                    let roll = motion.attitude.roll * 10
                    self.applyShadow(width: CGFloat(roll), height: CGFloat(pitch))
                }
            })
        }
    }
    
    private func applyShadow(width: CGFloat, height: CGFloat) {
        if let shadowView = shadowView {
            let shadowPath = UIBezierPath(roundedRect: shadowView.bounds, cornerRadius: 10.0)
            shadowView.layer.masksToBounds = false
            shadowView.layer.shadowRadius = 4.0
            shadowView.layer.shadowColor = UIColor.black.cgColor
            shadowView.layer.shadowOffset = CGSize(width: width, height: height)
            shadowView.layer.shadowOpacity = 0.05
            shadowView.layer.shadowPath = shadowPath.cgPath
        }
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("")
    }
    
    func configureSocialCount(_ socialCount: Int) {
        let accountsLabel = socialCount == 1 ? "Account" : "Accounts"
        countLabel.text = "\(socialCount) Social \(accountsLabel)"
    }
    
    func configureWithPic(_ imageAttachmentToken: DittoAttachmentToken?, _ collection: String) {
        guard let attachmentToken = imageAttachmentToken else {
            self.pictureImageView.image = nil
            return
        }
        thumbnailFetcher = Pic.getDataForAttachmentToken(attachmentToken, collection, { (progress, error, data, _) in
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
