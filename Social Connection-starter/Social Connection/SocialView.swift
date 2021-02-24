//
//  SocialView.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/18/21.
//

import Foundation
import UIKit


class SocialView: UIView {
    
    lazy var button: UIButton = {
        let button = UIButton()
        button.translatesAutoresizingMaskIntoConstraints = false
        button.backgroundColor = .clear
        button.layer.masksToBounds = true
        return button
    }()
    
    lazy var iconImageView: UIImageView = {
        let i = UIImageView()
        i.translatesAutoresizingMaskIntoConstraints = false
        i.contentMode = .scaleAspectFill
        i.backgroundColor = UIColor.clear
        return i
    }()

    lazy var nameLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textColor = .white
        label.textAlignment = .left
        label.font = UIFont.systemFont(ofSize: 16)
        return label
    }()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        layer.masksToBounds = true
        layer.cornerRadius = 30
        
        addSubview(iconImageView)
        addSubview(nameLabel)
        addSubview(button)
        
        iconImageView.centerYAnchor.constraint(equalTo: centerYAnchor).isActive = true
        iconImageView.centerXAnchor.constraint(equalTo: centerXAnchor, constant: -50).isActive = true
        iconImageView.heightAnchor.constraint(equalToConstant: 35).isActive = true
        iconImageView.widthAnchor.constraint(equalToConstant: 35).isActive = true
        
        nameLabel.topAnchor.constraint(equalTo: topAnchor,constant: 20).isActive = true
        nameLabel.bottomAnchor.constraint(equalTo: bottomAnchor,constant: -20).isActive = true
        nameLabel.leadingAnchor.constraint(equalTo: iconImageView.trailingAnchor, constant: 10).isActive = true
        
        
        button.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        button.topAnchor.constraint(equalTo: topAnchor).isActive = true
        button.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        button.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
