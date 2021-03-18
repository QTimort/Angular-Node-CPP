import { Component, OnInit } from '@angular/core';
import { ApiService } from '../../services/api.service';


// uncomment the following import in order to use Lodash
// import * as _ from 'lodash';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {
  users;

  constructor(private apiService: ApiService) {

  }

  ngOnInit(): void {
    this.apiService.getNews().subscribe((data)=>{
      this.users = data['users'];
    });
  }

}
