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

    }
    
    func setupRequestsList() {

    }
    
    @objc func acceptInvite(_ button: UIButton) {
        connectionsCollection.findByID(requests[button.tag].id).update { mutableDoc in
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
            performSegue(withIdentifier: "profileSegue", sender: connections[indexPath.row])
        }
    }
}
