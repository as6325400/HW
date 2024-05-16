<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\AuthController;
use App\Http\Controllers\UserController;
use App\Http\Controllers\VoteController;
 
Route::group([
    'middleware' => 'api',
    'prefix' => 'auth'
], function ($router) {
    Route::post('/register', [AuthController::class, 'register'])->name('register');
    Route::post('/login', [AuthController::class, 'login'])->name('login');
    Route::post('/logout', [AuthController::class, 'logout'])->middleware('auth:api')->name('logout');
    Route::post('/refresh', [AuthController::class, 'refresh'])->middleware('auth:api')->name('refresh');
    Route::post('/me', [AuthController::class, 'me'])->middleware('auth:api')->name('me');
});

Route::group([
    'middleware' => 'api',
    'prefix' => 'profile'
], function ($router) {
    Route::post('/userprofile', [UserController::class, 'userprofile'])->name('userprofile');
    Route::post('/updateimg', [UserController::class, 'updateimg'])->name('updateimg');
    Route::post('/getowntopics', [UserController::class, 'getowntopics'])->name('getowntopics');
});


Route::group([
    'middleware' => 'api',
    'prefix' => 'vote'
], function ($router) {
    Route::post('/createvote', [VoteController::class, 'createvote'])->name('createvote');
    Route::post('/deletevote', [VoteController::class, 'deletevote'])->name('deletevote');
    Route::post('/editvote', [VoteController::class, 'editvote'])->name('editvote');
    Route::post('/gettime', [VoteController::class, 'gettime'])->name('gettime');
    Route::post('/getallvotes', [VoteController::class, 'getallvotes'])->name('getallvotes');
});
