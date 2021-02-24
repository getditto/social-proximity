//
//  ViewController.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/13/21.
//

import UIKit
import DittoSyncKitSwift

class HomeViewController: UIViewController {
    
    
    let tableView : UITableView = {
        let tableView = UITableView(frame: .zero, style : .grouped)
        tableView.translatesAutoresizingMaskIntoConstraints = false
        tableView.showsVerticalScrollIndicator = false
        return tableView
    }()
    
    override func loadView() {
        super.loadView()
        tableView.dataSource = self
        tableView.delegate = self
        view.addSubview(tableView)
        tableView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor).isActive = true
        tableView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor).isActive = true
        tableView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor).isActive = true
        tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor).isActive = true
        tableView.separatorStyle = .none
        tableView.register(AttendeeTableViewCell.self, forCellReuseIdentifier: AttendeeTableViewCell.REUSE_ID)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.

        setupProfileList()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        insertUser()
    }
    
    func insertUser() {
        guard let user = Defaults.getUser() else {
            if let controller = self.tabBarController as? TabBarViewController {
                controller.goToEditProfile()
            }
            return
        }

    }
    
    func setupProfileList() {

    }
    
    @objc func sendInvite(_ sender: UIButton) {
        var superview = sender.superview
        while let view = superview, !(view is AttendeeTableViewCell) {
            superview = view.superview
        }
        guard let cell = superview as? AttendeeTableViewCell, let indexPath = tableView.indexPath(for: cell) else {
            return
        }

        
    }
}

extension HomeViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return profiles.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: AttendeeTableViewCell.REUSE_ID, for: indexPath) as! AttendeeTableViewCell
        return cell
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "Nearby"
    }
}

