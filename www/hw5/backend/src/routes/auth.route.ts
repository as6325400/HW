import AuthController from "../controllers/AuthController"
import Route from "./route";

class AuthRoute extends Route{
  private authController = new AuthController();

  constructor() {
    super();
    this.prefix = '/auth';
    this.setRoutes();
  }

  protected setRoutes() {
    this.router.get('/login', this.authController.echo);
    this.router.get('/test', this.authController.test);
  }
}

export default AuthRoute;