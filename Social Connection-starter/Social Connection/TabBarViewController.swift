//
//  TabBarViewController.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/15/21.
//

import UIKit
import DittoSyncKitSwift

class TabBarViewController: UITabBarController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.navigationItem.titleView = navTitleWithImageAndText(titleText: "Social", imageName: "icon")
    }

    func navTitleWithImageAndText(titleText: String, imageName: String) -> UIView {

        let titleView = UIView()
        let label = UILabel()
        label.text = titleText
        label.sizeToFit()
        label.center = titleView.center
        label.textAlignment = NSTextAlignment.center

        let image = UIImageView()
        image.image = UIImage(named: imageName)
        let imageAspect = image.image!.size.width / image.image!.size.height

        let imageX = label.frame.origin.x - label.frame.size.height * imageAspect
        let imageY = label.frame.origin.y

        let imageWidth = label.frame.size.height * imageAspect
        let imageHeight = label.frame.size.height

        image.frame = CGRect(x: imageX - 5, y: imageY, width: imageWidth, height: imageHeight)
        image.contentMode = UIView.ContentMode.scaleAspectFit
        titleView.addSubview(label)
        titleView.addSubview(image)
        titleView.sizeToFit()

        return titleView

    }
    
    @objc func goToEditProfile() {
        performSegue(withIdentifier: "editProfileSegue", sender: self)
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
