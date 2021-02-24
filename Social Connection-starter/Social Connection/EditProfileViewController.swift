//
//  ProfileViewController.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/14/21.
//

import Foundation
import UIKit
import Eureka

class EditProfileViewController: FormViewController {

    let imagePicker = UIImagePickerController()
    var imagePath: String?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        imagePath = Defaults.getUser()?.imagePath
        imagePicker.delegate = self
        navigationItem.rightBarButtonItem = UIBarButtonItem(title: "Save", style: .plain, target: self, action: #selector(saveInfo))
        form +++ Section("User Info")
            <<< TextRow(){ row in
                row.tag = "name"
                row.title = "Name"
                row.placeholder = "Full Name"
            }
        +++ Section("Social Accounts")
            <<< TextRow(){ row in
                row.tag = "linkedin"
                row.title = "Linkedin"
                row.placeholder = "Profile Name"
            }
            <<< TextRow(){ row in
                row.tag = "facebook"
                row.title = "Facebook"
                row.placeholder = "Profile Name"
            }
            <<< TextRow(){ row in
                row.tag = "instagram"
                row.title = "Instagram"
                row.placeholder = "@"
            }
            <<< TextRow(){ row in
                row.tag = "twitter"
                row.title = "Twitter"
                row.placeholder = "@"
            }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        if imagePath == nil {
            let alert = UIAlertController(title: "Conference Picture", message: "Let's take a photo/ for your profile", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "Got It", style: .default, handler: { (_) in
                self.imagePicker.sourceType = .camera
                self.imagePicker.allowsEditing = true
                self.imagePicker.cameraCaptureMode = .photo
                self.imagePicker.cameraDevice = .front
                self.present(self.imagePicker, animated: true, completion: nil)

            }))

            present(alert, animated: true, completion: nil)
        }
    }
    
    @objc func saveInfo() {
        guard let name: TextRow = form.rowBy(tag: "name"), let linkedin: TextRow = form.rowBy(tag: "linkedin"), let facebook: TextRow = form.rowBy(tag: "facebook"), let instagram: TextRow = form.rowBy(tag: "instagram"), let twitter: TextRow = form.rowBy(tag: "twitter"), let imagePath = self.imagePath else  { return }
        Defaults.saveUser(imagePath: imagePath, name: name.value ?? "", linkedin: linkedin.value ?? "", instagram: instagram.value ?? "", twitter: twitter.value ?? "", facebook: facebook.value ?? "")
        navigationController?.popViewController(animated: true)
    }
}

extension EditProfileViewController : UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        if let pickedImage = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            imagePath = Pic.insertPicture(image: pickedImage)
            self.dismiss(animated: true, completion: nil)
        }
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        dismiss(animated: true, completion: nil)
    }
}
