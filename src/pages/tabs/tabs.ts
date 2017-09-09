import { Component } from '@angular/core';

import { HomePage } from '../home/home';
import { ProfilePage } from '../profile/profile';
import { AboutPage } from '../about/about';

@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {


  tab1Root: any = HomePage;
  tab2Root: any = AboutPage;
  tab3Root: any = ProfilePage;


  constructor() {

  }
}
