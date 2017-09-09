import {AlertController, NavController} from 'ionic-angular';
import {Component} from '@angular/core';
import {BackandService} from '../../providers/backandService';

@Component({
  templateUrl: 'home.html',
  providers: [BackandService]
})
export class HomePage {
  todos = [];

  constructor(public nav: NavController, public backandService: BackandService, private alertCtrl: AlertController) {
    this.loadTodos();
  }

  private loadTodos() {
    this.backandService.getTodos()
    .subscribe(
      data => {
        this.todos = data.data;
      },
      err => this.logError(err)
    );
  }

  public todoSelected(item: {}) {
    console.log('selected item: ', item);
  }

  public createTodo() {
    let prompt = this.alertCtrl.create({
      title: 'New Todo',
      message: "What do you want to achieve?",
      inputs: [
        {
          name: 'name',
          placeholder: 'Name'
        }
      ],
      buttons: [
        {
          text: 'Cancel',
          handler: data => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Save',
          handler: data => {
            this.saveTodo(data.name);
          }
        }
      ]
    });
    prompt.present();
  }

  public saveTodo(name: string) {
    this.backandService.addTodo(name).subscribe(
      data => {
        this.todos.push(data);
      },
      err => this.logError(err)
    );
  }

  public removeTodo(id: string) {
    this.backandService.removeTodo(id).subscribe(
      data => {
        this.loadTodos();
      },
      err => this.logError(err)
    );
  }

  public logError(err: TemplateStringsArray) {
    console.error('Error: ' + err);
  }
}