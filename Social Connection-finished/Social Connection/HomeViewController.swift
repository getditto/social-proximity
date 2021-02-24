//
//  ViewController.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/13/21.
//

import UIKit
import DittoSyncKitSwift

class HomeViewController: UIViewController {
    
    var store: DittoStore!
    var liveQuery: DittoLiveQuery?
    var profilesCollection: DittoCollection!
    var connectionsCollection: DittoCollection!
    var profiles: [DittoDocument] = []
    
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
                
        store = Constants.ditto.store
        profilesCollection = store.collection("profiles")
        connectionsCollection = store.collection("connections")
        
        
        //invite use (from) UUID and (to) UUID
        //observe all UUID (to)
        //accept by sending UUID
        //to and from (invites) and connection default = false
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
        //Make sure the user doesn't already exist in the collection
        //If off a new install and already does will just throw an
        //error and not insert again
        let profile = profilesCollection.findByID(Defaults.getUserId()).exec()
        if profile == nil {
            let attachment = Constants.ditto.store["profiles"].newAttachment(path: (Defaults.getUser()?.imagePath)!)
            try! profilesCollection.insert([
                "name": user.name,
                "attachment": attachment,
                "mimeType": "image/jpeg",
                "instagram": Defaults.getUser()?.instagram,
                "linkedin": Defaults.getUser()?.linkedin,
                "facebook": Defaults.getUser()?.facebook,
                "twitter": Defaults.getUser()?.twitter,
                "socialCount": Defaults.getSocialCount()
            ], id: Defaults.getUserId())
        }
    }
    
    func setupProfileList() {
        liveQuery = profilesCollection.findAll().observe { [weak self] docs, event in
            guard let `self` = self else { return }
            switch event {
            case .update(let changes):
                guard changes.insertions.count > 0 || changes.deletions.count > 0 || changes.updates.count > 0  || changes.moves.count > 0 else { return }
                DispatchQueue.main.async {
                    self.tableView.beginUpdates()
                    self.tableView.performBatchUpdates({
                        let deletionIndexPaths = changes.deletions.map { idx -> IndexPath in
                            return IndexPath(row: idx, section: 0)
                        }
                        self.tableView.deleteRows(at: deletionIndexPaths, with: .automatic)
                        let insertionIndexPaths = changes.insertions.map { idx -> IndexPath in
                            return IndexPath(row: idx, section: 0)
                        }
                        self.tableView.insertRows(at: insertionIndexPaths, with: .automatic)
                        let updateIndexPaths = changes.updates.map { idx -> IndexPath in
                            return IndexPath(row: idx, section: 0)
                        }
                        self.tableView.reloadRows(at: updateIndexPaths, with: .automatic)
                        for move in changes.moves {
                            let from = IndexPath(row: move.from, section: 0)
                            let to = IndexPath(row: move.to, section: 0)
                            self.tableView.moveRow(at: from, to: to)
                        }
                    }) { _ in }
                    self.profiles = docs
                    self.tableView.endUpdates()
                }
            case .initial:
                self.profiles = docs
                DispatchQueue.main.async {
                    self.tableView.reloadData()
                }
            default: break
            }
        }
    }
    
    @objc func sendInvite(_ sender: UIButton) {
        var superview = sender.superview
        while let view = superview, !(view is AttendeeTableViewCell) {
            superview = view.superview
        }
        guard let cell = superview as? AttendeeTableViewCell, let indexPath = tableView.indexPath(for: cell) else {
            return
        }

        let profile = profiles[indexPath.row]
        //if a connection request has already been sent
        //then just add them as a connection and don't
        //create a duplicate connection request
        let connect = connectionsCollection.find("to == '\(Defaults.getUserId())' && from == '\(profile.id)'").exec()
        if connect.count > 0 {
            connectionsCollection.findByID(connect[0].id).update { mutableDoc in
                mutableDoc?["connected"].set(true)
            }
        } else {
            try! connectionsCollection.insert([
                "to": profile.id,
                "from": Defaults.getUserId(),
                "connected": false,
            ])
        }
        if let cell = tableView.cellForRow(at: IndexPath(row: indexPath.row, section: 0)) as? AttendeeTableViewCell {
            cell.inviteButton.isHidden = true
        }
    }
}

extension HomeViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return profiles.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: AttendeeTableViewCell.REUSE_ID, for: indexPath) as! AttendeeTableViewCell
        cell.inviteButton.tag = indexPath.row
        cell.inviteButton.addTarget(self, action: #selector(sendInvite(_:)), for: .touchUpInside)
        let profile = profiles[indexPath.row]
        cell.configureWithPic(profile["attachment"].attachmentToken, "profiles")
        cell.configureSocialCount(profile["socialCount"].intValue)
        if profile.id == Defaults.getUserId() {
            cell.nameLabel.text = "ME"
            cell.inviteButton.isHidden = true
        } else {
            let lal = connectionsCollection.find("(to == '\(profile.id)' && from == '\(Defaults.getUserId())') || (to == '\(Defaults.getUserId())' && from == '\(profile.id)')").exec()
            cell.inviteButton.isHidden = lal.count > 0
            cell.nameLabel.text = profile["name"].stringValue
        }
        return cell
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "Nearby"
    }
}

