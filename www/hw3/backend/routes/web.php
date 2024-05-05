<?php

use Illuminate\Support\Facades\Route;

Route::get('/', function () {
    $data = [
        'name' => 'John Doe',
        'age' => 25,
        'email' => 'sadasdad'
    ];
    // return view('welcome');
    return response()->json($data);
});
