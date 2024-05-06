<?php

use Illuminate\Support\Facades\Route;

Route::get('/', function () {
    // $data = [
    //     'name' => 'John Doe',
    //     'age' => 25,
    //     'email' => 'sadasdad'
    // ];
    $results = DB::select('select * from test');
    return $results;
    return view('welcome');
    // return response()->json($data);
});

Route::get('/register', function () {
    return view('welcome');
    // return response()->json($data);
});
