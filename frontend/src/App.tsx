import React from 'react';
import logo from './logo.svg';
import LoginForm from './LoginForm';
import './App.css';

export default function App() {
  return (
    <div className="App">
      <header className="App-header">
        <div className="shopping-list">
          <LoginForm />
        </div>
      </header>
    </div>
  );
}