//
//  Connections.swift
//  Social Connection
//
//  Created by Neil Ballard on 2/16/21.
//

import Foundation
import UIKit
import DittoSyncKitSwift

class ConnectionsViewController: UIViewController {
    var store: DittoStore!
    var connectionsCollection: DittoCollection!
    var profilesCollection: DittoCollection!
    var connectionsLiveQuery: DittoLiveQuery?
    var connections: [DittoDocument] = []
    var requests: [DittoDocument] = []
    var requestsLiveQuery: DittoLiveQuery?
    
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
        connectionsCollection = store.collection("connections")
        profilesCollection = store.collection("profiles")
        
        
        //invite use (from) UUID and (to) UUID
        //observe all UUID (to)
        //accept by sending UUID
        //to and from (invites) and connection default = false
        setupRequestsList()
        setupConnectionsList()
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        if let profileController = segue.destination as? ProfileViewController {
            if let document = sender as? DittoDocument {
                profileController.profile = document
            }
        }
    }
    
    func setupConnectionsList() {
        connectionsLiveQuery = connectionsCollection.find("(to == '\(Defaults.getUserId())' || from == '\(Defaults.getUserId())') && connected == true").observe { [weak self] docs, event in
            guard let `self` = self else { return }
            switch event {
            case .update(let changes):
                guard changes.insertions.count > 0 || changes.deletions.count > 0 || changes.updates.count > 0  || changes.moves.count > 0 else { return }
                DispatchQueue.main.async {
                    self.tableView.beginUpdates()
                    self.tableView.performBatchUpdates({
                        let deletionIndexPaths = changes.deletions.map { idx -> IndexPath in
                            return IndexPath(row: idx, section: 1)
                        }
                        self.tableView.deleteRows(at: deletionIndexPaths, with: .automatic)
                        let insertionIndexPaths = changes.insertions.map { idx -> IndexPath in
                            return IndexPath(row: idx, section: 1)
                        }
                        self.tableView.insertRows(at: insertionIndexPaths, with: .automatic)
                        let updateIndexPaths = changes.updates.map { idx -> IndexPath in
                            return IndexPath(row: idx, section: 1)
                        }
                        self.tableView.reloadRows(at: updateIndexPaths, with: .automatic)
                        for move in changes.moves {
                            let from = IndexPath(row: move.from, section: 1)
                            let to = IndexPath(row: move.to, section: 1)
                            self.tableView.moveRow(at: from, to: to)
                        }
                    }) { _ in }
                    self.connections = docs
                    self.tableView.endUpdates()
                }
            case .initial:
                self.connections = docs
                DispatchQueue.main.async {
                    self.tableView.reloadData()
                }
            default: break
            }
        }
    }
    
    func setupRequestsList() {
        requestsLiveQuery = connectionsCollection.find("to == '\(Defaults.getUserId())' && connected == false").observe { [weak self] docs, event in
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
                    self.requests = docs
                    self.tableView.endUpdates()
                }
            case .initial:
                self.requests = docs
                DispatchQueue.main.async {
                    self.tableView.reloadData()
                }
            default: break
            }
        }
    }
    
    @objc func acceptInvite(_ sender: UIButton) {
        var superview = sender.superview
        while let view = superview, !(view is AttendeeTableViewCell) {
            superview = view.superview
        }
        guard let cell = superview as? AttendeeTableViewCell, let indexPath = tableView.indexPath(for: cell) else {
            return
        }
        
        connectionsCollection.findByID(requests[indexPath.row].id).update { mutableDoc in
            mutableDoc?["connected"].set(true)
        }
    }
}

extension ConnectionsViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == 0 {
            return requests.count
        }
        
        return connections.count
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: AttendeeTableViewCell.REUSE_ID, for: indexPath) as! AttendeeTableViewCell
        if indexPath.section == 0 {
            let request = requests[indexPath.row]
            if let profile = profilesCollection.findByID(request["from"].stringValue).exec() {
                cell.configureWithPic(profile["attachment"].attachmentToken, "connections")
                cell.configureSocialCount(profile["socialCount"].intValue)
                cell.nameLabel.text = profile["name"].stringValue
            }
            cell.inviteButton.isHidden = false
            cell.inviteButton.setTitle("Accept", for: .normal)
            cell.borderView.layer.borderWidth = 0.5
            cell.inviteButton.addTarget(self, action: #selector(acceptInvite(_:)), for: .touchUpInside)
        } else {
            let connection = connections[indexPath.row]
            cell.inviteButton.isHidden = true
            cell.borderView.layer.borderWidth = 2
            if connection["to"].stringValue == Defaults.getUserId() {
                if let profile = profilesCollection.findByID(connection["from"].stringValue).exec() {
                    cell.nameLabel.text = profile["name"].stringValue
                    cell.configureSocialCount(profile["socialCount"].intValue)
                    cell.configureWithPic(profile["attachment"].attachmentToken, "connections")
                }
            } else {
                if let profile = profilesCollection.findByID(connection["to"].stringValue).exec() {
                    cell.configureSocialCount(profile["socialCount"].intValue)
                    cell.nameLabel.text = profile["name"].stringValue
                    cell.configureWithPic(profile["attachment"].attachmentToken, "connections")
                }
            }
        }
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        if section == 0 {
            return "Requests"
        }
        
        return "Connections"
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        if indexPath.section == 1 {
            let val = connections[indexPath.row]["to"].stringValue == Defaults.getUserId() ? "from" : "to"
            let profile = profilesCollection.findByID(connections[indexPath.row][val].stringValue).exec()
            performSegue(withIdentifier: "profileSegue", sender: profile)
        }
    }
}
